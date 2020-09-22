#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <time.h>
#include <string.h>
#include "HashTable.h"
#include <sys/wait.h>


#define SHMKEY1 (key_t) 4321 //shared memory keys
#define SEMKEY1 (key_t) 4567 //semaphore keys
#define SEMKEY2 (key_t) 5678
#define SEMKEY3 (key_t) 6789
#define SEMKEY4 (key_t) 7890
#define SEMKEY5 (key_t) 8901
#define SEMKEY6 (key_t) 9012
#define PERMS 0600



int shm_Process_Manager;
Message *shm_Process_Manager_ptr;

int sem_Process_0,sem_Process_1,sem_Paragwgos_0,sem_Paragwgos_1,sem_Katanalwtis_0,sem_Katanalwtis_1,sem_Manager;
int shmsize;


union semun {
   int val;                  	/* value for SETVAL */
   struct semid_ds *buf;     /* buffer for IPC_STAT, IPC_SET */
   unsigned short *array;    /* array for GETALL, SETALL */

};

int isNumber(char* number);
int sem_wait(int sem_id); 
int sem_signal(int sem_id);
int sem_Init(int sem_id, int val);
void CreateResources();
void FreeResources(int f1,int f2,int f3,int f4,int f5,int f6,int f7);
void InitSemaphores();	//arxikopoiei ta semaphores
void putinSharedMemory(Component c,Component *shm); //vazei sti shared memory ta stoixeia tou component
void takefromSharedMemory(Component *shm,Component *c); //pairnei apo tin shared memory ta stoixeia tou component
void Manager(int k,int q,int max);
void Process_0(int q,int max);
void Process_1(int q,int max);
void Read_from_file();














