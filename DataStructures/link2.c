/* Implementation of a 2-way linked list. Inlcudes function to add(at index or at end),
   delete (at index or at begin.), print, and reverse the list */
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>

struct node{
	int value;
	struct node *prev;
	struct node *next;
};
struct node *head = NULL;
struct node *tail = NULL;

void add_node(int new_data);
void add_at_index(int new_data, int index);
void print_list(void);
void delete_node(int value);
void delete_at_index(int index);
void reverse_list(void);

int main(void){
	char instruction[10];
	int value, index;
	//double total_time;
	//clock_t start, end;
	
	srand(time(0));
	printf("Enter the instructions: \n");
	
	/*for(int i = 0; i < 200000; i++){
		add_node(i);
	}*/
	
	scanf("%s", &instruction);
	while(strcmp(instruction, "end") != 0){
		if(strcmp(instruction, "addv") == 0){
			scanf("%d", &value);
			
		//	start = clock();
			add_node(value);
		//	end = clock();
		//	total_time = (double)(end - start)/ CLOCKS_PER_SEC;
			//printf("The time spent to add a node: %lf\n", total_time);
		//	total_time = 0;
		}	
		else if(strcmp(instruction, "addi") == 0){
			scanf("%d", &value);
			scanf("%d", &index);
			
		//	start = clock();
			add_at_index(value,index);
		//	end = clock();
		//	total_time = (double)(end - start)/ CLOCKS_PER_SEC;
		//	printf("The time spent to add a node at index: %lf\n", total_time);
		//	total_time = 0;
		}
		else if(strcmp(instruction, "delv") == 0){
			scanf("%d", &value);
			
		//	start = clock();
			delete_node(value);
		//	end = clock();
		//	total_time = (double)(end - start)/ CLOCKS_PER_SEC;
			//printf("The time spent to delete a value: %lf\n", total_time);
		//	total_time = 0;
		}
		else if(strcmp(instruction, "deli") == 0){
			scanf("%d", &index);
			
		//	start = clock();
			delete_at_index(index);
		//	end = clock();
		//	total_time = (double)(end - start)/ CLOCKS_PER_SEC;
			//printf("The time spent to delete at index: %lf\n", total_time);
		//	total_time = 0;
		}
		else if(strcmp(instruction, "print") == 0){
			print_list();
		
		}
		else if(strcmp(instruction, "revs") == 0){
		//	start = clock();
			reverse_list();
		//	end = clock();
		//	total_time = (double)(end - start)/ CLOCKS_PER_SEC;
			//printf("The time spent to reverse a list: %lf\n", total_time);
		//	total_time = 0;
			
		}
		else{
			printf("Invalid instruction.\n");
		}
		
		scanf("%s", &instruction);
	}
		
	return 0;
}

void reverse_list(void){
	struct node *temp_1 = head, *temp_2 = tail;
	
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
	temp_2 = head;
	head = tail;
	tail = temp_2;
}
void add_node(int new_data) {
	struct node *new_node, *temp_node = head;
	
	new_node = (struct node*) malloc(sizeof(struct node));
	new_node->value = new_data;
	new_node->next = NULL;
	
	if(head == NULL) {
		head = new_node;
		tail = new_node;
	}
	else{
		tail->next = new_node;
		new_node->prev = tail;
		tail = tail->next;
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
			tail = new_node;
			
		}
		else{
			temp_node = head;
			while(temp_node->next != NULL && counter < index-1) {
				temp_node = temp_node->next;
				counter++;
			}
			new_node->next = temp_node->next;
			new_node->prev = temp_node->prev;
			temp_node->next = new_node;
		}
	}
}
void delete_node(int value){
	struct node *temp_node = head, *next_guy;
	if (head ==NULL){
		printf("Not found\n");
	} 
	else if(head->value == value){
		if(head == tail){
			next_guy = head;
			head = NULL;
			tail = NULL;
			free(next_guy);
		}
		else{
			next_guy = head;
			head = head->next;
			head->prev = NULL;
			free(next_guy);
		}
	}
	else{
		while(temp_node->next != NULL && temp_node->value != value){
			temp_node = temp_node->next;
		}
		
		if(temp_node->value == value){
			if(temp_node->next == NULL){
				temp_node->prev->next = NULL;
				tail = temp_node->prev; 
				free(temp_node);
			}
			else{
				temp_node->prev->next = temp_node->next;
				temp_node->next->prev = temp_node->prev;
				free(temp_node);
			}
		
		}
		else{
			printf("Value not found.\n");
		}
		
	}
}
////////////////////////////////////////////////////////////////
/////////////////  delete at index  ////////////////////////////
void delete_at_index(int index) {	
	int counter = 0;
	
	struct node *temp_node = head, *next_guy;
	
	if(index == 0){
		if(head == NULL){
			printf("Not found.\n");
		}
		else if(head == tail){
			next_guy = head;
			head = NULL;
			tail = NULL;
			free(next_guy);
		}
		else{
			next_guy = head;
			head = head->next;
			head->prev = NULL;
			free(next_guy);
		}
	}
	else{	
		while(counter < index && temp_node->next != NULL){
			temp_node = temp_node->next;
			//printf("Temp: %d\n", temp_node->value);
			counter++;	
			//printf("Counter: %d\n", counter);
		}
		if (counter == index){

			if(temp_node == tail){
				temp_node->prev->next = NULL;
				tail = temp_node->prev;
				free(temp_node);
			}

		/*	if(temp_node->next == NULL){
				temp_node->prev->next = NULL;
				tail = temp_node-> prev;
				free(temp_node);
			}*/
			else{
				temp_node->prev->next = temp_node->next;
				temp_node->next->prev = temp_node->prev;
				free(temp_node);
			}
		} else {
			printf("Get out of here!\n");
		}
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
	printf("\n");
}
