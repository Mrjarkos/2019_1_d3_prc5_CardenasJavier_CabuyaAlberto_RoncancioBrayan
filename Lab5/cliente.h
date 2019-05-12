#ifndef CLIENTE_H
#define CLIENTE_H

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <semaphore.h>
#include <math.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>        
#include <fcntl.h>  
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/wait.h>

typedef struct{
	unsigned char subscription_flag;
	char name_client[81];
	char id_client[81];
	unsigned char result_flag;
	pid_t my_pid;
}mem;

sem_t* sharedmem;
sem_t* cajero;
pid_t my_pid;
const char *name_semMem = "/smp_MemoriaCompartida";
const char *name_semCajero = "/smp_Cajero";
const char *mem_name="SHMEM_BANK";

void sigint(int a);
#endif
