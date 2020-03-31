/* Erika Ambrioso
	CSE2010
	Assignment 5a
	Basic implementation of a skip list of integers
*/

/* A skip list is a data strucure that can search a sorted list in 
	O(n) time. We implememt it with a few function including insert,
	delte, new_level, and rand_level.  */


#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<limits.h>


typedef struct Node{						
	int value;
	struct Node *left;
	struct Node *right;
	struct Node *above;
	struct Node *below;
} Node;

typedef struct List{
	int height;
	struct Node *header;
}List;

void new_level(List **, Node*, Node *);
void insert(List **, int data);
int rand_level();
void delete(List **, int data);
int search(List **my_list, int data);	
void print_skip(List **);
int main(void){
	int x = 11;
	
	List *my_list = (List*)malloc(sizeof(struct List));
	my_list->header = NULL;
	my_list->height =0;
	
	new_level(&my_list, NULL, NULL);						// the creation of the very first level
	
	// this is some test data used to demonstrate how the skip list works
	insert(&my_list, 22);
	print_skip(&my_list);
	insert(&my_list, 44);
	print_skip(&my_list);
	insert(&my_list, 11);
	print_skip(&my_list);
	insert(&my_list, 33);
	print_skip(&my_list);
	insert(&my_list, 55);
		
	printf("Skip List: \n");				// print the bottom level of the list
	print_skip(&my_list);
	
	if(search(&my_list, x) == 1){					// prints if value was found through the search
		printf("%d was found\n", x);
	}
	else{
		printf("%d was not found\n");
	}
	delete(&my_list, x);
	
	
	printf("Skip List after deletion: \n");				// print the bottom level of the list
	print_skip(&my_list);
	
	if(search(&my_list, x) == 1){					// prints if value was found through the search
		printf("%d was found\n", x);
	}
	else{
		printf("%d was not found\n");
	}
}

// adds a new level to the skiplist using the current top level pinters and returns the new topmost -inf.
void new_level(List **my_list, Node *curr_begin, Node *curr_end){
	struct Node *new_begin = (Node*)malloc(sizeof(struct Node));		// create -inf and +inf nodes..
	struct Node *new_end = (Node*)malloc(sizeof(struct Node));
	(*my_list)->header = new_begin;
	if(curr_begin != NULL){
		curr_begin->above = new_begin;
		curr_end->above = new_end;
	}
	// -inf pointers
	new_begin->left = NULL;											
	new_begin->right = new_end;
	new_begin->above = NULL;
	new_begin->below = curr_begin;
	// +inf pointers
	new_end->left = new_begin;											
	new_end->right = NULL;
	new_end->above = NULL;
	new_end->below = curr_end;
	// give values
	new_begin->value = INT_MIN;
	new_end->value = INT_MAX;
	
	(*my_list)->height++;
	// printf("Height: %d\n", (*my_list)->height);
	}	
// find the ordered postion to add the desired data and adds it
void insert(List **my_list, int data){
	Node *temp = (*my_list)->header;
	int heads = 0, add = 0;
	// first we need to find the position to put the value...this will be when the next is greater and the prev. is less
						// find the postion at the last level of the list
	while(temp->below != NULL){		
		while(data > temp->right->value){				
			temp = temp->right;
		}
		temp = temp->below;
	}

	// INSERTION TIME!!!
	heads = rand_level();
	add = heads-((*my_list)->height-1) ;				// simulation of coin flip--> returns number of heads
	if(add < 0){
		add = 0;
	}
	printf("Heads: %d\n", heads);
	for(int i = 0; i < add; i++){		// adds the neccessary number of new levels
		new_level(my_list, (*my_list)->header, (*my_list)->header->right);
	}
	for(int i = 0; i < heads+1; i++){
		Node *new_node = (Node *)malloc(sizeof(Node));				// create the node
		new_node->value = data;
		new_node->right = temp->right;										// adjust the pointers using the temp
		new_node->left = temp;
		new_node->above = NULL;
		temp->right = new_node;
		new_node->right->left = new_node;
		if(i ==0){
			new_node->below = NULL;
		}
		else{
			new_node->below = temp->below->right;
			new_node->below->above = new_node;
		}
		temp = temp->above;
	}
}
// returns a random number to be used as the levels that a value will be entered in	
int rand_level(){
	int level = 1;
	int x = rand()%2;
	while(x == 1){
		level++;
		x = rand()%2;
	}
	return level;
}
//deletes the desired value in all levels that it exists
void delete(List **my_list, int data){
	// search for the topmost instance of the value
	// while you are not dropping below the lowest level, adjust the pointers to delete the node
	// check for duplicate rows and delete if poosible
	Node *temp = (*my_list)->header;
	while(temp->below != NULL){						// loop to check the top level first
		while(data >= temp->right->value && (temp->right->value != INT_MAX)){		
			if(temp->value != data){
				temp = temp->right;
			}
			else if (temp->value == data){					// DELETE
				Node *temp2 = temp;
				temp2->left->right = temp2->right;
				temp2->right->left = temp2->left;
				free(temp2);
			}
		}
		temp = temp->below;				// drop to next level
	}
	temp->left->right = temp->right;				// final deleteion... the bottom level
	temp->right->left = temp->left;
	free(temp);
}
// returns a 0 if the value is not found and a one if it is
int search(List **my_list, int data){
	Node *temp = (*my_list)->header;
	while(temp->below != NULL){						// loop to check the top level first
		while(temp->value <= data){		
			if(temp->value == data){
				return 1;
			}
			else{
				temp = temp->right;
			}
		}
		temp = temp->below;				// drop to next level
	}
	return 0;
}	
// prints the lowest level of the skip list...for now!
void print_skip(List **my_list){
	Node *temp = (*my_list)->header;
	
	while(temp->below != NULL){
		temp= temp->right;
		while(temp->value != INT_MAX){
			printf("%d->", temp->value);
			temp= temp->right;
		}
		printf("\n");
		temp = temp->below;
		while(temp->value != INT_MIN){
			temp = temp->left;
		}
	}
	
		while(temp->value != INT_MIN){
			temp = temp->left;
		}
		while(temp->value != INT_MAX){
			printf("%d->", temp->value);
			temp= temp->right;
		}
		printf("\n");
	
}