//single linked list. Airport name 2.5 Exercise
// BROKEN CODE
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef char AirportCode[4];

typedef struct NodeType {
			AirportCode Airport;
			struct NodeType *Link;
		}NodeType;
NodeType *L, *M, *N;

void InsertNewFirstNode(AirportCode A){
	N = (NodeType*)malloc(sizeof(NodeType));
	//if the list empty
	if (L == NULL){
		strcpy(N->Airport,A);
		L = N;
	}
	else {
		strcpy(N->Airport,A);
		N->Link = L;
		L = N;
	}
}
void DeleteFirst(){
	if (L != NULL) {
		if (L->Link == NULL){
			free(L);
		}
		else {
			NodeType *temp; 

			temp = L;
			L = L->Link;
			free(temp);
		}
	}
}
void Print(){
	NodeType *temp = L;
	while(temp->Link != NULL){
		printf("%c ",temp->Airport);
		temp= temp->Link;
	}
}
int main(){
	AirportCode code;
	printf("Enter AirportCode to insert: ");
	scanf("%s",code);
	InsertNewFirstNode(code);
	Print();

	return 0;
}