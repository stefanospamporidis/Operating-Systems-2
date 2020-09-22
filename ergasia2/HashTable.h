#ifndef HashTable_H
#define HashTable_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


#define ROWS 7
#define COLUMNS 2


typedef struct{
	char address[9];
	char action;

}Message;

// this struct is what a queue node should contain (and every other usefull variable inside it)
typedef struct {
	char page_number[6];
	int frame_number;

}Component;

// this is a queue node declaration
typedef struct qn {				
	Component component;
	struct qn *next;
}QueueNode;

typedef struct {			
	QueueNode *head; // points head queue node
	QueueNode *tail; // points last queue node
	int count;	// keep the number of queue nodes		
}Queue;

typedef struct{
	int read_counter;
	int write_counter;
	int total_frames;
	int reserved_frames_1;
	int reserved_frames_2;
	int pfs1;
	int pfs2;
	Queue h_table[ROWS][COLUMNS];
}HashTable;

//Our Hash Table Interface
void initHashTable(HashTable * hashtable,int frames); //HashTable initialization
int hex_to_int(char * hex); //metatrepei 16diko string se dekadiko
int hash_function(char * address); //metatrepei ti dieu8unsi se ari8mo gia na mpei sto hash_table
void Flush(HashTable * hashtable,int pid); //diagrafei olous tous komvous pou aforoun tin diergasia pid
void Find_Page(HashTable * hashtable,char *address,char action,int pid,int k); //ftiaxnei dia8esimo plaisio an den uparxei i dieu8unsi sto hashtable kai an den uparxei dia8esimo plaisio kanei flush ta stoixeia tis katallilis ouras

// Our queue interface
void FreeQueue(Queue * queue); //eleu8erwnei tin oura
void initQueue(Queue * queue);  // Queue initialization
void addNode(Queue * queue, Component component); // add a component in queue end
int removeNode(Queue * queue, Component *component);	// remove a component from head
void printQueue(Queue * queue); // print queue content
void copyComponent(Component *source,Component *target); //copy components
int queueIsEmpty(Queue * queue); //tsekarw an einai adeia i oura
int Is_Page_Exist(Queue * queue,Component * component); //elegxei an uparxei i selida stin oura
void Insert(HashTable * hashtable,Component component);
#endif




