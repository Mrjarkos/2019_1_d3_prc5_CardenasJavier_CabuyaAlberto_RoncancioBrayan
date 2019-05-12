#ifndef PRUEBA_H
#define PRUEBA_H

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

#define BUFFER_SIZE 3

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

typedef struct {
    int id;
    bool status;
    pid_t pid_client;
   	char name_client[81];
	char id_client[81];
} arg_thread;

sem_t* sharedmem;
sem_t* cajero; 
int freecash, NCajeros, shm_fd, size;
mem* memoria;
void* ptr;
bool* hilo_estado; //false = disponible
volatile int in, out, clientes_banco;
client* buffer_clientes;
const char *name_semMem = "/smp_MemoriaCompartida";
const char *name_semCajero = "/smp_Cajero";
const char *mem_name="SHMEM_BANK";
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *Ingreso_Clientes(void * a);
void *Atender_Clientes(void *a);
void sigint(int a);

#endif
