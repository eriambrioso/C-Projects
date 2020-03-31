/* Implementation of sorting a doublely(2-way) link list of integer values
	as well as sorting an array with an iterative method

	The code will print out the list of values and the sorted array. 
	Then the sorting of the link list begins and prints each step
 */

#include<stdio.h>
#include<stdlib.h>
#include <math.h>
#include <time.h>

struct node{
	int value;
	struct node *prev;
	struct node *next;
};

struct node *head = NULL;
struct node *tail = NULL;

void sort_array(int array[], int size);
void sort_link_list(void);
void print_list(void);
void add_node(int);

/* Driver function */
int main(void){
	int size = 10;
	int array[] = {1, 88, 82, 80, 41, 29, 55, 65, 11, 62};
	int r;
	
	
	srand(time(0));
	
	printf("The array is:\n");
	for(int i = 0; i < size; i++){
		r = rand()% 100;	
		//array[i] = r;
		add_node(array[i]);
		printf("%d ", array[i]);
	}
	printf("\n\n");
	sort_array(array, size);
	
	printf("The sorted array is: \n");
	for(int j = 0; j < size; j++){
		printf("%d ", array[j]);
	}
	printf("\n\n");
	
	printf("Linked list:\n");
	print_list();

	sort_link_list();
	printf("The sorted link list is:\n");
	print_list();
	return 0;
}
/* Iterative implentaion of sorting an array of variable size */
void sort_array(int array[], int size){
	int min_i =0, temp, index;
	
	for(int j = 0; j < size-1; j++){
		min_i = j;
		for(int i = j+1; i < size; i++){
			if(array[i] < array[min_i]){
				min_i = i;
			}
		}
		if(min_i != j){
			temp = array[j];
			array[j] = array[min_i];
			array[min_i] = temp;
		}
	}
	
}
/////////////////////////////////////////////////////////////////////////
/////////////////////////  sort link list  //////////////////////////////
void sort_link_list(void){
	struct node *i, *j, *min, *temp, *start, *other_temp;
	int count = 0;
    for(i = head; i->next != NULL;){
        min = i;
		count++;
        for(j = i->next; j->next!=NULL ; j=j->next){
            if(j->value < min->value){
				min = j;

			}	
		}
		if(j->value < min->value){
			min = j;
		}
        if(min != i){

			if(i == head){
				start = i;
				if (min != tail){
					min->next->prev = start;
				}else{
					tail = start;
				}
				if(start->next != min){
					min->prev->next = start;
					start->next->prev = min;
					temp = start->next;
					start->next = min->next;
					
					min->next = temp;
					
					start->prev= min->prev;
					
					min->prev = NULL;
					
					head = min;
					i = min->next;
				}
				else{
					start->next->prev = start->prev;
					temp = start->next;
					start->next = min;
					min->next = start;
					start->prev->next = min;
					temp = start->prev;
					start->prev = min;
					min->prev = temp;
					i = min->next;
				}
			}
			else{
				start = i;
				if(min != tail){
					min->next->prev = start;
				}
				else{
					tail = start;
				}
				printf("Start next: %d\n", start->next->value);
				if(start->next == min){
					min->prev->next = min->next;
				}else{
					min->prev->next = start;
				}
				start->prev->next = min;
				
				if(start->next == min){
					start->next->prev = start->prev;
				}else{
					start->next->prev = min;
				}
				temp = start->next;
				start->next = min->next;
	
				if(start->next == min){
					min->next = start;
				}else{
					min->next = temp;
				}
				temp = start->prev;
				if(start->next == min){
					start->prev = min;
				}else{
					start->prev= min->prev;
				}
				min->prev = temp;
				print_list();
     			i = min->next;

			}
						
				// printf("i :%d\n", i->value );	
        }
		else{
			 i=i->next;
		}
	}
}

/////////////////////////////////////////////////////////////////////////
/////////////////////////  add node  ////////////////////////////////////
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
//////////////////////////////////////////////////////////////////////////
///////////////////////  print link list  ////////////////////////////////
void print_list(void){
	struct node *temp_node = head;
	
	if(head != NULL){
		while(temp_node->next != NULL) {
			printf("%d ", temp_node->value);
			temp_node = temp_node->next;
		}
		printf("%d ", temp_node->value);
	}		
	printf("\n\n");
}
