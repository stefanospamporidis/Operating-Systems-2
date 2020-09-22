#include "askisi2.h"

int isNumber(char* number){ //tsekarw an dinw ari8mo apo to pliktrologio
	int i;
	for (i=0;i<strlen(number);i++){
		if (number[i]<'0' || number[i]>'9')
			return 0;
	}
	return 1;
}	


/* Semaphore down operation, using semop */
int sem_wait(int sem_id) {
   struct sembuf sem_d;
   
   sem_d.sem_num = 0;
   sem_d.sem_op = -1;
   sem_d.sem_flg = 0;
   if (semop(sem_id,&sem_d,1) == -1) {
       perror("# Semaphore down operation ");
       return -1;
   }
   return 0;
}

/* Semaphore up operation, using semop */
int sem_signal(int sem_id) {
   struct sembuf sem_d;
   
   sem_d.sem_num = 0;
   sem_d.sem_op = 1;
   sem_d.sem_flg = 0;
   if (semop(sem_id,&sem_d,1) == -1) {
       perror("# Semaphore up operation ");
       return -1;
   }
   return 0;
}

/* Semaphore Init - set a semaphore's value to val */
int sem_Init(int sem_id, int val) {

   union semun arg;
   
   arg.val = val;
   if (semctl(sem_id,0,SETVAL,arg) == -1) {
       perror("# Semaphore setting value ");
       return -1;
   }
   return 0;

}

void CreateResources(){
	shmsize =  sizeof(Message);
	//ftiaxnoume shared memory   
	shm_Process_Manager = shmget (SHMKEY1, shmsize, PERMS | IPC_CREAT);
	if ( shm_Process_Manager < 0 ) {
    	FreeResources(0,0,0,0,0,0,0);
    }
	
	//kanoume attach tis mnimes 
	shm_Process_Manager_ptr = (Message*)shmat(shm_Process_Manager, (char *) 0, 0);
	if ( shm_Process_Manager_ptr == NULL ) {
    	FreeResources(1,0,0,0,0,0,0);        
    }

	//Create a new semaphore
	sem_Process_0 = semget(SEMKEY1,1,IPC_CREAT | 0660);
   	if (sem_Process_0 == -1) {
       	FreeResources(1,1,0,0,0,0,0);
   	}
	//Create a new semaphore
	sem_Process_1 = semget(SEMKEY2,1,IPC_CREAT | 0660);
   	if (sem_Process_1 == -1) {
       	FreeResources(1,1,1,0,0,0,0);
   	}
	sem_Paragwgos_0 = semget(SEMKEY3,1,IPC_CREAT | 0660);
   	if (sem_Paragwgos_0 == -1) {
       	FreeResources(1,1,1,1,0,0,0);
   	}
	sem_Paragwgos_1 = semget(SEMKEY4,1,IPC_CREAT | 0660);
   	if (sem_Paragwgos_1 == -1) {
       	FreeResources(1,1,1,1,1,0,0);
   	}
	sem_Katanalwtis_0 = semget(SEMKEY5,1,IPC_CREAT | 0660);
   	if (sem_Katanalwtis_0 == -1) {
       	FreeResources(1,1,1,1,1,1,0);
   	}
	sem_Katanalwtis_1 = semget(SEMKEY6,1,IPC_CREAT | 0660);
	if (sem_Katanalwtis_1 == -1) {
       	FreeResources(1,1,1,1,1,1,1);
   	}
	
}


void FreeResources(int f1,int f2,int f3,int f4,int f5,int f6,int f7){

	if (f1 == 1){
		if (shmctl(shm_Process_Manager,IPC_RMID,(struct shmid_ds *)NULL) < 0){
			perror("shm_Process_Manager \n");
			exit(1);
		}			
	}
	if (f2 == 1){
		if (shmctl(shm_Process_Manager,IPC_RMID,(struct shmid_ds *)NULL) < 0){
			perror("shm_Process_Manager \n");
			exit(1);
		}		
	}
	if (f3 == 1){
		if (shmctl(shm_Process_Manager,IPC_RMID,(struct shmid_ds *)NULL) < 0){
			perror("shm_Process_Manager \n");
			exit(1);
		}	
	}
	if (f4 == 1){
		if (shmctl(shm_Process_Manager,IPC_RMID,(struct shmid_ds *)NULL) < 0){
			perror("shm_Process_Manager \n");
			exit(1);
		}	
	}
	if (f5 == 1){
		if (shmctl(shm_Process_Manager,IPC_RMID,(struct shmid_ds *)NULL) < 0){
			perror("shm_Process_Manager \n");
			exit(1);
		}	
	}
	if (f6 == 1){
		if (shmctl(shm_Process_Manager,IPC_RMID,(struct shmid_ds *)NULL) < 0){
			perror("shm_Process_Manager \n");
			exit(1);
		}	
	}
	if (f7 == 1){
		if (shmctl(shm_Process_Manager,IPC_RMID,(struct shmid_ds *)NULL) < 0){
			perror("shm_Process_Manager \n");
			exit(1);
		}	
	}
	exit(1);

}

void InitSemaphores(){

	//Semaphores initialization
   	/* Set the value of the semaphore to 1 */
   	if (sem_Init(sem_Process_0, 0) == -1) { 
       		FreeResources(1,1,0,0,0,0,0);
   	}
	if (sem_Init(sem_Process_1, 0) == -1) { 
       		FreeResources(1,1,1,0,0,0,0);
   	}
	if (sem_Init(sem_Paragwgos_0, 1) == -1) { 
       		FreeResources(1,1,1,1,0,0,0);
   	}
	if (sem_Init(sem_Paragwgos_1, 1) == -1) { 
       		FreeResources(1,1,1,1,1,0,0);
   	}
	if (sem_Init(sem_Katanalwtis_0, 0) == -1) { 
       		FreeResources(1,1,1,1,1,1,0);
   	}
	if (sem_Init(sem_Katanalwtis_1, 0) == -1) { 
       		FreeResources(1,1,1,1,1,1,1);
   	}
	
}

void Process_0(int q,int max){
	
	int count=0,i;
	
	char line[64];
	char *address;
	FILE* file1 = fopen("bzip.trace","r");	
	while (1){
		sem_wait(sem_Process_0);
		for (i=0; i<q; i++){
			sem_wait(sem_Paragwgos_0);
			printf("Eimai o paragwgos0 \n");
			if (fgets(line,sizeof(line),file1) == NULL){
				break;		
			}
			char *token = strtok(line," \n");
			strcpy(shm_Process_Manager_ptr->address,token);
			
			token = strtok(NULL," \n");
			shm_Process_Manager_ptr->action = token[0];
			count++;
			sem_signal(sem_Katanalwtis_0);
			if (count == max )
				break;
		}
		if (count == max )
			break;
	}
	fclose(file1);
	exit(0);
}

void Process_1(int q,int max){

	int count=0,i;
	
	char line[64];
	char *address;
	FILE* file1 = fopen("gcc.trace","r");	
	while (1){
		sem_wait(sem_Process_1);
		for (i=0; i<q; i++){
			sem_wait(sem_Paragwgos_1);
			printf("Eimai o paragwgos1 \n");
			if (fgets(line,sizeof(line),file1) == NULL){
				break;			
			}
			char *token = strtok(line," \n");
			strcpy(shm_Process_Manager_ptr->address,token);
			
			token = strtok(NULL," \n");
			shm_Process_Manager_ptr->action = token[0];
			count++;
			sem_signal(sem_Katanalwtis_1);
			if (count == max )
				break;
		}
		if (count == max )
			break;
	}
	fclose(file1);
	exit(0);
}

void Manager(int k,int q,int max){

	int i,count1=0,count2=0;
	char address[9],action;
	Component c;
	HashTable hashtable;
	initHashTable(&hashtable,k);
	while (1){
		sem_signal(sem_Process_0);
		for (i=0;i<q;i++){
			sem_wait(sem_Katanalwtis_0);
			printf("Eimai o manager \n");
			strcpy(address,shm_Process_Manager_ptr->address);
			action=shm_Process_Manager_ptr->action;
			Find_Page(&hashtable,address,action,0,k);
			count1++;
			sem_signal(sem_Paragwgos_0);
			if (count1 == max)
				break;
		}
		sem_signal(sem_Process_1);
		for (i=0;i<q;i++){
			sem_wait(sem_Katanalwtis_1);
			printf("Eimai o manager \n");
			strcpy(address,shm_Process_Manager_ptr->address);
			action=shm_Process_Manager_ptr->action;
			Find_Page(&hashtable,address,action,1,k);
			count2++;
			sem_signal(sem_Paragwgos_1);
			if (count2 == max)
				break;
		}
		if (count1 == max && count2 == max)
				break;	
	}
	printf("read counter: %d\n",hashtable.read_counter);
	printf("write counter: %d\n",hashtable.write_counter);
	printf("total frames: %d\n",hashtable.total_frames);
	printf("reserved frames 1: %d\n",hashtable.reserved_frames_1);
	printf("reserved frames 2: %d\n",hashtable.reserved_frames_2);
	printf("page faults process 0: %d\n",hashtable.pfs1);
	printf("page faults process 1: %d\n",hashtable.pfs2);
}


int main ( int argc , char * argv []) {
	
	int i,k,ari8mos_plaisiwn,q,max,status;
	pid_t pid,wpid;
	if (argc != 5){
		printf("La8os ari8mos orismatwn\n");
		exit(1);
	}
	if (isNumber(argv[1]) == 0 ){
		printf("La8os ari8mos sta orismata\n");
		exit(1);
	}
	if (isNumber(argv[2]) == 0 ){
		printf("La8os ari8mos sta orismata\n");
		exit(1);
	}
	if (isNumber(argv[3]) == 0 ){
		printf("La8os ari8mos sta orismata\n");
		exit(1);
	}
	if (isNumber(argv[4]) == 0 ){
		printf("La8os ari8mos sta orismata\n");
		exit(1);
	}
	k=atoi(argv[1]); // ari8mos epitreptwn page faults,otan 3eperastei kanw flush
	ari8mos_plaisiwn=atoi(argv[2]); // ari8mos plaisiwn prepei na einai toulaxiston 2 fores megaluteros tou k
	if (ari8mos_plaisiwn < 2*k ){
		printf("La8os ari8mos sta orismata\n");
		exit(1);	
	}
	q=atoi(argv[3]); //o ari8mos pou upodeilwnei ka8e posa ixni anaforas 8a allazw process diladi diavazw q ixni anaforas kai pigainw apo to process1 sto process2
	max=atoi(argv[4]); //posa ixni anaforas na diavazw apo to ka8ena diladi an diavazw 20 prepei na diavasw 20 apo to 1o arxeio kai 20 apo to 2o
	if (max < q){
		printf("La8os ari8mos sta orismata\n");
		exit(1);	
	}
	CreateResources(); //edw 8a kaleitai i create resources
	InitSemaphores();

	pid=fork();
	if (pid == 0)
		Process_0(q,max);
	
	pid=fork();
	if (pid == 0)
		Process_1(q,max);
	
	Manager(k,q,max);

	while((wpid=wait(&status)) > 0 ){
		printf("teleiwse i %u\n",wpid);
	}
	FreeResources(1,1,1,1,1,1,1);
	printf("eimai i main \n");
	return 0;
}





























