/* Implementation of a single link list including functions to
   add or delete elements, print, or reverse the list. Important
   to review the expected input to manipulate the list as desired. */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <math.h>

struct node{
	int value;
	struct node *next;
};
struct node *head = NULL;

void add_node(int new_data);
void add_at_index(int new_data, int index);
void print_list(void);
void delete_node(int value);
void delete_at_index(int new_data, int index);
void reverse_list(void);

int main(void){
	char instruction[10];
	int value, index;
	
	printf("Enter the instructions: \n");
	
	scanf("%s", &instruction);
	while(strcmp(instruction, "end") != 0){
		if(strcmp(instruction, "addv") == 0){
			scanf("%d", &value);
			add_node(value);
		}	
		else if(strcmp(instruction, "addi") == 0){
			scanf("%d", &value);
			scanf("%d", &index);
			
			add_at_index(value,index);
		}
		else if(strcmp(instruction, "delv") == 0){
			scanf("%d", &value);
			delete_node(value);
		}
		else if(strcmp(instruction, "deli") == 0){
			scanf("%d", &index);
			delete_at_index(value, index);
		}
		else if(strcmp(instruction, "print") == 0){
			print_list();
		
		}
		else if(strcmp(instruction, "revs") == 0){
			reverse_list();
		}
		else{
			printf("Invalid instruction.\n");
		}
		
		scanf("%s", &instruction);
	}
		
	return 0;
}

void reverse_list(void){
	struct node *temp_1 = head, *temp_2 = head, *tail;

	while(temp_1->next != NULL){
		temp_1 = temp_1->next;
	}
	tail = temp_1;
	while(temp_1 != head){
		temp_2 = head;
		while(temp_2->next != temp_1){
			temp_2 = temp_2->next;
		}
		temp_1->next = temp_2;
		temp_1 = temp_2;
	}
	head->next = NULL;
	head = tail;
}
void add_node(int new_data) {
	struct node *new_node, *temp_node;
	new_node = (struct node*) malloc(sizeof(struct node));
	new_node->value = new_data;
	new_node->next = NULL;
	
	if(head == NULL) {
		head = new_node;
	} else {
		temp_node = head;
		while(temp_node->next != NULL) {
			temp_node = temp_node->next;
		}
	temp_node->next = new_node;
	}
}
void add_at_index(int new_data, int index) {	
	int counter = 0;
	
	struct node *new_node, *temp_node;
	new_node = (struct node*) malloc(sizeof(struct node));
	new_node->value = new_data;
	new_node->next = NULL;
	
	if(head == NULL) {
		head = new_node;
	}
	else {
		if(index == 0){
			new_node->next = head;
			head = new_node;
			
		}
		else{
			temp_node = head;
			while(temp_node->next != NULL && counter < index) {
				temp_node = temp_node->next;
				counter++;
			}
			new_node->next = temp_node->next;
			temp_node->next = new_node;
		}
	}
}
void delete_node(int value){
	struct node *temp_node = head, *next_guy;
	
	if(head->value == value){
		next_guy = head;
		head = head->next;
		free(next_guy);
	}	
	else{
		while(temp_node->next != NULL){
			if(temp_node->next->value == value){
				next_guy = temp_node->next;
				temp_node->next = temp_node->next->next;
				free(next_guy);
				break;
			}
			temp_node = temp_node->next;
		}
	}
}
void delete_at_index(int new_data, int index) {	
	int counter = 1;
	
	struct node *temp_node = head, *next_guy;
	
	if(index == 0){
		next_guy = head;
		head = head->next;
		free(next_guy);
	
	}
	else{	
		while(counter < index){
			temp_node = temp_node->next;
			counter++;	
		}
		next_guy = temp_node->next;
		temp_node->next = temp_node->next->next;
		free(next_guy);
	}	
}
void print_list(void){

	struct node *temp_node = head;
	
	if(head != NULL){
		while(temp_node->next != NULL) {
			printf("%d ", temp_node->value);
			temp_node = temp_node->next;
		}
		printf("%d ", temp_node->value);
	}		
}
