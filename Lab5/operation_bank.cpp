#include "operation_bank.h"
#include "threaddatos.h"

Operation_Bank::Operation_Bank()
{
    N_Cajeros = 10;
    Operation_Bank(N_Cajeros);

}
Operation_Bank::~Operation_Bank()
{
            sem_close(sharedmem);
            sem_unlink(name_semMem);
            sem_close(cajero);
            sem_unlink(name_semCajero);
            shm_unlink(mem_name);
            exit(0);
}

Operation_Bank::Operation_Bank(int N_Cajeros){

    buffer_clientes = new client[BUFFER_SIZE]; //Como el banco es pequeño, solo pueden haber BUFFER_SIZE personas maximo
    in = 0;
    out = 0;
    clientes_banco=0;
    freecash=N_Cajeros;
    size = sizeof(mem);

    //pthread_create(&ingreso, NULL, Ingreso_Clientes, NULL);
    sharedmem = sem_open(name_semMem, O_CREAT|O_EXCL, 0644, 1);
    cajero = sem_open(name_semCajero, O_CREAT|O_EXCL, 0644, N_Cajeros);

    hilo_estado = new bool[N_Cajeros];

    for (int i = 0; i < N_Cajeros; ++i) {hilo_estado[i] = false;}

    //pthread_create(&ingreso, NULL, Ingreso_Clientes, NULL);
}

bool Operation_Bank::Crear_Memoria_Compartida(){
     shm_fd = shm_open(mem_name, O_CREAT|O_RDWR|O_EXCL, 0666);
        if (shm_fd==-1) {return true;}
     ftruncate(shm_fd, size);
     ptr = mmap(0, size, PROT_WRITE, MAP_SHARED, shm_fd, 0);
     memoria = (mem*)ptr;
     memoria->subscription_flag = (unsigned char)0;
     memoria->result_flag = (unsigned char)0;
     close(shm_fd);
     shm_fd = shm_open(mem_name, O_RDWR, 0666);
     return false;
}

void Operation_Bank::R_Mem(){
    pthread_create(& ingreso, NULL, &Operation_Bank::Leer_Memoria, this);
}

void Operation_Bank::Ingreso_Clientes(){
    while (1) {
        //printf("\n[I] Ingreso de Clientes \n");
        ptr = mmap(0, size, PROT_READ, MAP_SHARED, shm_fd, 0);
        //printf("[I] Esperando a que un cliente llegue...\n");
            do{
                memoria = (mem*)ptr;
            }while(memoria->subscription_flag==(unsigned char)0);

        //printf("[I] Se solicito ingreso\n");

        if((in+1)%BUFFER_SIZE == out){
            printf("[I] Banco lleno, Esperando a que un cliente termine se vaya...\n");
            while((in+1)%BUFFER_SIZE == out);
        }

        strcpy(buffer_clientes[in].name_client, memoria->name_client);
        //printf("Nombre = %s\n", buffer_clientes[in].name_client );
        strcpy(buffer_clientes[in].id_client, memoria->id_client);
        buffer_clientes[in].pid_client = memoria->my_pid;
        //printf("id = %s\n", buffer_clientes[in].id_client);
        sleep(1); //Para hacer mas evidente la cola al ingresar

        pthread_mutex_lock(&mutex);
        in= (in+1)%BUFFER_SIZE;
        clientes_banco++;
        pthread_mutex_unlock(&mutex);

        ptr = mmap(0, size, PROT_WRITE, MAP_SHARED, shm_fd, 0);
        memoria = (mem*)ptr;
        memoria->subscription_flag = (unsigned char)0;

        //printf("[I] Cliente ingreso\n");

    }

}



