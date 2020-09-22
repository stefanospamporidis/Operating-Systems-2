#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "HashTable.h"

void initHashTable(HashTable * hashtable,int frames){
	int i;
	hashtable->read_counter=0;
	hashtable->write_counter=0;
	hashtable->total_frames=frames;
	hashtable->reserved_frames_1=0;
	hashtable->reserved_frames_2=0;
	hashtable->pfs1=0;
	hashtable->pfs2=0;
	for (i=0;i<ROWS;i++){
		initQueue(&(hashtable->h_table[i][0]));	
		initQueue(&(hashtable->h_table[i][1]));
	}
}

void Flush(HashTable * hashtable,int pid){
	int i;
	for (i=0;i<ROWS;i++)
		FreeQueue(&(hashtable->h_table[i][pid]));
}

void Find_Page(HashTable * hashtable,char *address,char action,int pid,int k){ //to pid prepei na einai 0 i 1
	int position,IsExist;
	char hex[6];
	memset(hex,'\0',sizeof(hex)); //arxikopoiei me 0 ton pinaka hex
	strncpy(hex,address,5*sizeof(char)); //kanei copy mesa ston pinaka to adress
	Component component;
	strcpy(component.page_number,hex);
	position=hash_function(hex);
	IsExist=Is_Page_Exist(&(hashtable->h_table[position][pid]), &component);
	if (action=='R')
		hashtable->read_counter++;
	else
		hashtable->write_counter++;
	if (IsExist==1){
		return;
	}
	//i selida den uparxei
	(pid==0)? hashtable->pfs1++: hashtable->pfs2++;
	if (pid==0 && hashtable->reserved_frames_1== k){
		Flush(hashtable,pid);	
		hashtable->reserved_frames_1=1; //to vazw 1 giati meta 8a pros8esw neo plaisio
	}
	else if (pid==1 && hashtable->reserved_frames_2== k){
		Flush(hashtable,pid);
		hashtable->reserved_frames_2=1;	//to vazw 1 giati meta 8a pros8esw neo plaisio
	}
	addNode(&(hashtable->h_table[position][pid]),component);
}


int Is_Page_Exist(Queue * queue,Component * component){
	QueueNode * temp=queue->head;
	while (temp!=NULL){
		if (!strcmp(component->page_number,temp->component.page_number))
			return 1;	
		temp=temp->next;
	}
	return 0;
}


int hex_to_int(char * hex){ //metatrepei to 16diko se ari8mo

	return ((int)strtol(hex,NULL,16));

}

int hash_function(char * address){

	return hex_to_int(address)%ROWS;

}


void initQueue(Queue * queue){
	queue->head=NULL;
	queue->tail=NULL;
	queue->count=0;
}

void FreeQueue(Queue * queue){

	if (queue->count==0)
		return;
	QueueNode *temp=queue->head;
	while (temp!=NULL){
		queue->head=queue->head->next;
		free(temp);
		temp=queue->head;	
	}
	queue->head=NULL;
	queue->tail=NULL;
	queue->count=0;

}

void addNode(Queue * queue, Component component){
	QueueNode *temp = (QueueNode*)malloc(sizeof(QueueNode));
	strcpy(temp->component.page_number,component.page_number);
	temp->component.frame_number=component.frame_number;
	temp->next=NULL;
	// If queue is empty, then new node is front and rear both 
	if(queue->head==NULL && queue->tail==NULL){
		queue->head=queue->tail=temp;
		queue->count++;
		return;
	}
	// Add the new node at the end of queue and change rear
	queue->tail->next=temp;
	queue->tail=temp;
	queue->count++;	
}

int removeNode(Queue * queue,Component *component){
	//If queue is empty, return NULL.
	if (queue->count == 0){
		return 0;
	}
	QueueNode *temp=queue->head;
	queue->head=queue->head->next;
	queue->count=queue->count-1;
	// after removing we check if there are no more nodes make the queue empty,we could do it with count too
	if (queue->count == 0) 
       queue->tail = NULL; 
	copyComponent(&(temp->component),component);
	free(temp);
    return 1;
}

void copyComponent(Component *source,Component *target){
	strcpy(target->page_number,source->page_number);
	target->frame_number=source->frame_number;
}

void printQueue(Queue * queue){
	QueueNode* temp=queue->head;
	while (temp!=NULL){
		printf("%s-> ",temp->component.page_number);
		printf("%d-> ",temp->component.frame_number);
		temp=temp->next;
	}
	printf("\n");
}

int queueIsEmpty(Queue * queue){

	return queue->count==0;

}





