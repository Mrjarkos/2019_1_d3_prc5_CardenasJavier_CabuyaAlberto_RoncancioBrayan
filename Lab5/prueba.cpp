#include "prueba.h"

int main(int argc, char *argv[])
{	
	buffer_clientes = new client[BUFFER_SIZE]; //Como el banco es pequeño, solo pueden haber BUFFER_SIZE personas maximo
	in = 0;
	out = 0;
	clientes_banco=0;
	size = sizeof(mem);
	pthread_t atender, ingreso;

    if(argc==2){
        NCajeros = atoi(argv[1]);
      }else{
        printf("Numero invalido de argumentos\n");
        printf("Estructura: ./prueba #Cajeros\n");
        return 0;
      }

    signal(SIGINT,sigint);
    printf("Bienvenido al programa de prueba del cliente\n");
    printf("Creando Semaforos...\n");
    sharedmem = sem_open(name_semMem, O_CREAT|O_EXCL, 0644, 1);
    cajero = sem_open(name_semCajero, O_CREAT|O_EXCL, 0644, NCajeros);

    printf("Creando Memoria Compartida\n");
    shm_fd = shm_open(mem_name, O_CREAT|O_RDWR|O_EXCL, 0666);
		if (shm_fd==-1){
				printf("Banco ya abierto\n");
				shm_unlink(mem_name);
				return 1;
		}

    ftruncate(shm_fd, size);
	ptr = mmap(0, size, PROT_WRITE, MAP_SHARED, shm_fd, 0);
	memoria = (mem*)ptr;
	memoria->subscription_flag = (unsigned char)0;
	memoria->result_flag = (unsigned char)0;
	close(shm_fd);
    printf("Memoria Compartida Lista\n");

    shm_fd = shm_open(mem_name, O_RDWR, 0666);
    
    pthread_create(&ingreso, NULL, Ingreso_Clientes, NULL);
    pthread_create(&atender, NULL, Atender_Clientes, NULL);
    pthread_join(ingreso, NULL);
    pthread_join(atender, NULL);

    return 0;
}

void sigint(int a){
		sem_close(sharedmem);
		sem_unlink(name_semMem);
		sem_close(cajero);
		sem_unlink(name_semCajero);
		shm_unlink(mem_name);
		exit(0);	
	} 

void *Ingreso_Clientes(void *a){
	while(1){

  		printf("\n[I] Ingreso de Clientes \n");
  		printf("[I] Asientos Disponibles = %i\n", BUFFER_SIZE-clientes_banco);
    	sem_getvalue(cajero, &freecash);
    	ptr = mmap(0, size, PROT_READ, MAP_SHARED, shm_fd, 0);

			do{
				memoria = (mem*)ptr;
			}while(memoria->subscription_flag==(unsigned char)0);	

		printf("[I] Se solicito ingreso\n");

		if((in+1)%BUFFER_SIZE == out){
			printf("[I] Banco lleno, Esperando a que un cliente termine se vaya...\n");
			while((in+1)%BUFFER_SIZE == out);
		}

		strcpy(buffer_clientes[in].name_client, memoria->name_client);
		//printf("Nombre = %s\n", buffer_clientes[in].name_client );
		strcpy(buffer_clientes[in].id_client, memoria->id_client);
		//printf("id = %s\n", buffer_clientes[in].id_client);
		sleep(5); //Para hacer mas evidente la cola al ingresar
		
		pthread_mutex_lock(&mutex);
		in= (in+1)%BUFFER_SIZE;
		clientes_banco++;
		pthread_mutex_unlock(&mutex);
		
		ptr = mmap(0, size, PROT_WRITE, MAP_SHARED, shm_fd, 0);
		memoria = (mem*)ptr;
		memoria->subscription_flag = (unsigned char)0;

		printf("[I] Cliente ingreso\n");
	}
}

void *Atender_Clientes(void *a){
	while(1){
		sem_getvalue(cajero, &freecash);
		printf("\n[A] Atender Clientes\n");
    	printf("[A] Cajeros Libres = %i\n", freecash);
		if(in == out){
			printf("[A] Cajeros Libres, Esperando a que un cliente llegue...\n");
			while(in == out);
		}

		if(freecash==0){
			printf("[A] Cajero lleno, Esperando a que un cliente termine...\n");
			while(freecash==0){
			sem_getvalue(cajero, &freecash);				
			}
		}

		printf("[%i] Atendiendo a:\n");
		printf("[%i] Nombre = %s\n", buffer_clientes[out].name_client );
		printf("[%i] id = %s\n", buffer_clientes[out].id_client);
		pthread_mutex_lock(&mutex);
		out = (out + 1) % BUFFER_SIZE;
		clientes_banco--;
		pthread_mutex_unlock(&mutex);
		
		
		printf("[%i] Cliente Atendido\n");
	}
}
