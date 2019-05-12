#include "cliente.h"

int main(int argc, char *argv[])
{
    signal(SIGINT,sigint);
    my_pid = getpid();
	int shm_fd, size = sizeof(mem);;
	void* ptr;
	mem* memoria;
	char name_client[81], id_client[81];

    if(argc==3){
        if(strlen(argv[1])>80){
        	printf("Nombre demasiado largo\n");
        	return 0;
        }else{
        	strcpy(name_client, argv[1]);
        }
        if(strlen(argv[2])>80){
        	printf("id demasiado largo\n");
        	return 0 ;
        }else{
        	strcpy(id_client, argv[2]);
        }
      }else{
        printf("Numero invalido de argumentos\n");
        printf("Estructura: ./cliente name id\n");
        return 0;
      }
    printf("Datos del cliente:\n");
    printf("Pid = %d\n", my_pid);
    printf("Nombre: %s \nId: %s\n", name_client, id_client);

    sharedmem = sem_open(name_semMem, 0);
    printf("\nEsperando por entrar al banco\n");
    
    if(sharedmem==SEM_FAILED){
        printf("Banco cerrado\n");
        return 1;
    }

    sem_wait(sharedmem);

    shm_fd = shm_open(mem_name, O_RDWR, 0666);
    	if (shm_fd==-1){
			printf("Banco cerrado\n");
			return 1;
		}

    printf("\nBienvenido al banco Kranks Bank\n");
    printf("\nEntrando al banco\n");
    printf("Solicitando Asignacion de Turno\n");
    ptr = mmap(0, size, PROT_WRITE , MAP_SHARED, shm_fd, 0);
    memoria = (mem*)ptr;
    strcpy(memoria->name_client, name_client);
    memoria->name_client[80]='\0';
    strcpy(memoria->id_client, id_client);
    memoria->id_client[80]='\0';
    memoria->subscription_flag = (unsigned char)1;
    memoria->my_pid = my_pid;
    //printf("Memoria compartida escrita\n");
    ptr = mmap(0, size, PROT_READ, MAP_SHARED, shm_fd, 0);
    memoria = (mem*)ptr;
    printf("Esperando Asignacion de Turno\n");
    while(memoria->subscription_flag == (unsigned char)1);
  	sem_post(sharedmem);
   

    cajero = sem_open(name_semCajero, 0);
    printf("\nTurno asignado\nEsperando Turno\n");
    sem_wait(cajero);
    printf("Turno Obtenido\n");
    printf("\nRealizando transacciones\n");
    sleep(rand()%15+5);
    sem_post(cajero);

    printf("\nCliente Feliz\n");
    printf("Cliente se fue\n");
    return 0;
}

void sigint(int a){
        sem_close(sharedmem);
        sem_close(cajero);
        exit(0);    
    } 
