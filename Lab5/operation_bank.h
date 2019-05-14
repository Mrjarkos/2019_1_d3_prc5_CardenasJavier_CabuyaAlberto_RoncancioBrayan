#ifndef OPERATION_BANK_H
#define OPERATION_BANK_H

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <semaphore.h>
#include <math.h>
#include <signal.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <pthread.h>

#define BUFFER_SIZE 10


typedef struct{
    unsigned char subscription_flag;
    char name_client[81];
    char id_client[81];
    unsigned char result_flag;
    pid_t my_pid;
}mem;

typedef struct{
    char name_client[81];
    char id_client[81];
    pid_t pid_client;
}client;

//typedef struct {
//    int id;
//    bool* status;
//    pid_t pid_client;
//    char name_client[81];
//    char id_client[81];
//} arg_thread;

class Operation_Bank
{
public:
    static void* Leer_Memoria(void* object){
        reinterpret_cast<Operation_Bank*>(object)->Ingreso_Clientes();
        return 0;
    }

    static void* Atend_Client(void* object){
        reinterpret_cast<Operation_Bank*>(object)->Asignar_Turno();
        return 0;
    }

    static void* Atender_Al_Cliente(void* object){
        reinterpret_cast<Operation_Bank*>(object)->Atender_Clientes();
        return 0;
    }

    
    int freecash;
    bool* hilo_estado; //false = disponible
    volatile int in, out, clientes_banco;
    client* buffer_clientes;
    client* cajero_clientes;

    Operation_Bank();
    Operation_Bank(int N_Cajeros);
    ~Operation_Bank();
   bool Crear_Memoria_Compartida();
   void R_Mem();
   void A_Cli();



private:

    sem_t* sharedmem;
    sem_t* cajero;
    int shm_fd, size;
    int N_Cajeros, hilo;
    mem* memoria;
    void* ptr;
    const char *name_semMem = "/smp_MemoriaCompartida";
    const char *name_semCajero = "/smp_Cajero";
    const char *mem_name="SHMEM_BANK";

    pthread_t atender, ingreso;
    //pthread_t *Cajeros_h;
   // pthread_attr_t *attr;
    //arg_thread data[10];
    //arg_thread data[10];

    pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

    void Ingreso_Clientes();
    void Asignar_Turno();
    void* Atender_Clientes();
   // static void* Leer_Memoria(void* object);
};

#endif // OPERATION_BANK_H
