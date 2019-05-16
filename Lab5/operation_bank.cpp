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
    printf("inicializando variables\n");
    this->N_Cajeros = N_Cajeros;
    buffer_clientes = new client[BUFFER_SIZE]; //Como el banco es pequeño, solo pueden haber BUFFER_SIZE personas maximo
    cajero_clientes = new client[N_Cajeros];
    in = 0;
    out = 0;
    clientes_banco=0;
    freecash = N_Cajeros;
    size = sizeof(mem);
    hilo = 0;
    //pthread_create(&ingreso, NULL, Ingreso_Clientes, NULL);
    sharedmem = sem_open(name_semMem, O_CREAT|O_EXCL, 0644, 1);
    cajero = sem_open(name_semCajero, O_CREAT|O_EXCL, 0644, N_Cajeros);

    //hilo_estado = new bool[N_Cajeros];

    for (int i = 0; i < N_Cajeros; ++i)
    {
        hilo_estado[i] = false;
        cajero_clientes[i].pid_client=0;
    }
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
    pthread_create(&ingreso, NULL, &Operation_Bank::Leer_Memoria, this);
}

void Operation_Bank::A_Cli(){
    pthread_create(&atender, NULL, &Operation_Bank::Atend_Client, this);
}

void Operation_Bank::S_hilos(){
    pthread_create(&see, NULL, &Operation_Bank::See_hilos, this);
}

void Operation_Bank::Mirar_hilos(){
    while(1){
       // while(freecash==0);
       // while(freecash!=0);
        pthread_mutex_lock(&mutex);
            for(int j=0; j<N_Cajeros; j++){
                if(cajero_clientes[j].pid_client != NULL){
                    if(!hilo_estado[j]){
                        cajero_clientes[j].pid_client = NULL;
                    }
                }
            }
         pthread_mutex_unlock(&mutex);
    }
}

void Operation_Bank::Ingreso_Clientes(){
    while (1) {
        //printf("\n[I] Ingreso de Clientes \n");
        ptr = mmap(0, size, PROT_READ, MAP_SHARED, shm_fd, 0);
        printf("[I] Esperando a que un cliente llegue...\n");
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

void Operation_Bank::Asignar_Turno(){
        pthread_t Cajeros_h[N_Cajeros];
        pthread_attr_t attr[N_Cajeros];
        bool estado;
    while(1){
          sem_getvalue(cajero, &freecash);

          if(in == out){
              printf("[A] Cajeros Libres, Esperando a que un cliente llegue...\n");
              while(in == out);
          }

          if(freecash==0){
              printf("[A] Cajero lleno, Esperando a que un cliente termine...\n");
              while(freecash==0){ //Cajero lleno, Esperando a que un cliente termine...\n");
              sem_getvalue(cajero, &freecash);
              }
          }
         // usleep(1000*1000);

          for (int i = 0; i < N_Cajeros; ++i)
          {
              usleep(1000*200);
              pthread_mutex_lock(&mutex);
              estado = hilo_estado[i];
              pthread_mutex_unlock(&mutex);

              if(!estado){
                  pthread_mutex_lock(&mutex);
                  hilo_estado[i]= true;
                  printf("[%i] Entro al hilo\n", i);
                  hilo = i;
                  cajero_clientes[i].pid_client = buffer_clientes[out].pid_client;
                  strcpy(cajero_clientes[i].name_client, buffer_clientes[out].name_client);
                  strcpy(cajero_clientes[i].id_client, buffer_clientes[out].id_client);
                  pthread_mutex_unlock(&mutex);
                  pthread_attr_init(&attr[i]);
                  pthread_create(&Cajeros_h[i], &attr[i], Atender_Al_Cliente, this);
              break;
              }
          }
         usleep(1000*500);
      }
}

void* Operation_Bank::Atender_Clientes(){

        int i = 0;
        client* myclient = new client;
        char statFileName[128];
        FILE *fd;
        pthread_mutex_lock(&mutex);
        sem_getvalue(cajero, &freecash);
        i = hilo;
        printf("[%i] Entro al hilo\n", i);
        myclient->pid_client = cajero_clientes[i].pid_client;
        strcpy(myclient->name_client, cajero_clientes[i].name_client);
        strcpy(myclient->id_client, cajero_clientes[i].id_client);
        this->out = (this->out + 1) % BUFFER_SIZE;
       // printf("[A] Liberar out; out = %i\n", out);
        clientes_banco--;
        pthread_mutex_unlock(&mutex);

        sprintf(statFileName, "/proc/%d/stat", myclient->pid_client);
        printf("[%i] Esperando a que el cliente termine....\n", i);
        do{
            fd = fopen(statFileName, "r");
            if (fd != NULL){
                fclose(fd);
            }
        }while(fd!=NULL);
        hilo_estado[i] = false;
        sem_getvalue(cajero, &freecash);
        pthread_exit(NULL);

}


