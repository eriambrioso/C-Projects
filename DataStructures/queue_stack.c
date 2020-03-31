/* Erika Ambrioso
	CSE2010
	Assignment 3a 
	Circular Queue and a stack
*/
#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>

#define MAXSIZE 15

typedef int item_type;

typedef struct Queue{						// queue structure (no count, only front and rear)
	int front;
	int rear;
	item_type items[MAXSIZE];
} Queue;
		
typedef struct Stack{						// stack structure
	int count;
	char items[MAXSIZE];
} Stack;

//Queue functions
void initialize(Queue **Q);
int empty(Queue *Q);
int full(Queue *Q);
void insert(item_type R, Queue **Q);
void remove_from(Queue **, item_type *);
void print_queue(Queue **Q);
//Stack functions
void push(Stack **S, item_type *X);
void pop(Stack **S, item_type *X);
void print_stack(Stack **S);

void reverse(Queue **Q, Stack **S, item_type *X);

int main(void){
	struct Queue *Q = (Queue*)malloc(sizeof(Queue));			// malloc space for the queue and stack
	struct Stack *S = (Stack*)malloc(sizeof(Stack));
	S->count = 0;
	//print_stack(&S);
	int i = 0;
	item_type R;
	initialize(&Q);
	printf("Empty: %d\n", empty(Q));
	printf("Full: %d\n", full(Q));
	
	for(int i = 0; i <10;i++){
		insert(i, &Q);
	}
	print_queue(&Q);
	
	//remove_from(&Q, &R);
	
	print_queue(&Q);
	printf("Empty: %d\n", empty(Q));
	printf("Full: %d\n", full(Q));

	// REVERSE
	while(empty(Q) != 1){
		remove_from(&Q, &R);
		push(&S, &R);
	}
	
	print_stack(&S);

}


/*******Initializes the front of the Q array as 0 position*************/
void initialize(Queue **Q){
	(*Q)->front = 0;
	(*Q)-> rear = 0;
}
/********1 for true 0 for false****************************************/
int empty(Queue *Q){
	if(Q->rear == Q->front){
		return 1;
	}
	else{
		return 0;
	}
}
/*********1 for true 0 for false***************************************/
int full(Queue *Q){
	if(Q->front == (Q->rear +1)%(MAXSIZE-1)){
		return 1;
	}
	else{
		return 0;
	}
}
/**********inserts desired item at the end******************************/
void insert(item_type R, Queue **Q){
	if(full(*Q) == 1){					// first check if there is space to add
		printf("Error, full queue %d\n");	
	}
	else{
		(*Q)->items[(*Q)->rear] = R;
		(*Q)->rear = ((*Q)->rear +1)%(MAXSIZE-1);
	}
}
/*****removes desired item at unknown position**************************/
void remove_from(Queue **Q, item_type *F){				// check if there is anything to remove
	if(empty(*Q) == 1){
		printf("Error. Empty queue\n");
	}
	else{
		*F = (*Q)->items[(*Q)->front];
		(*Q)->front = ((*Q)->front +1)%MAXSIZE;
	}
}
/*********prints the queue first to last*********************************/
void print_queue(Queue **Q){
	printf("Queue items: ");
	for(int i = (*Q)->front; i<(*Q)->rear; i=(i+1)%MAXSIZE){
		printf("%d ", (*Q)->items[i]);
	}
	printf("\n");
}
/*****pushes item onto top of stack**************************************/
void push(Stack **S, item_type *X){
	(*S)->items[(*S)->count] = *X;
	(*S)->count++;
}	
/*******removes item at top of stack*************************************/
void pop(Stack **S, item_type *X){
	if((*S)->count == 0){
		printf("Error, empty stack.\n");			// check if empty stqak
	}
	else{
		(*S)->count--;
		*X = (*S)->items[(*S)->count];
	}
}	
/******prints the stack**************************************************/
void print_stack(Stack **S){
	printf("Stack items: ");
	int i = (*S)->count-1;
	while(i >=0){					// while not at the end
		printf("%c ", (*S)->items[i]);
		i--;
	}
}