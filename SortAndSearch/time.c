/* Sorts an array and linked list of desired size
   and prints the time it takes. Currently the program
   runs on a size of 20000 values */

#include<stdio.h>
#include<stdlib.h>
#include <time.h>
#include <math.h>

struct node{
	int value;
	struct node *prev;
	struct node *next;
};

struct node *head = NULL;
struct node *tail = NULL;

void sort_array(int array[]);
void sort_link_list(void);
void print_list(void);
void add_node(int);

int main(void){
	int size = 20000, r;
	int array[size];	
	double array_t, list_t;
	clock_t start_t, end_t;
	srand(time(0));
	
	printf("The size is %d\n\n", size);
	for(int i = 0; i < size; i++){
		r = rand()% 30000;	
		array[i] = r;
		add_node(r);
	}
	
	start_t = clock();
	sort_array(array);
	end_t = clock();
	array_t = (double)(end_t - start_t)/ CLOCKS_PER_SEC;
	printf("The time spent for an array: %lf\n\n", array_t);
	
	start_t = clock();
	sort_link_list();
	end_t = clock();
	list_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
	printf("The time spent for a linked list: %.3lf\n\n", list_t);
	
	return 0;
}

void sort_array(int array[]){
	int min = array[0], temp, index;
	
	for(int j = 0; j < 10; j++){
		min = array[j];
		for(int i = j; i < 10; i++){
			if(array[i] < min){
				min = array[i];
				index = i;
				temp = array[j];
				array[j] = min;
				array[i] = temp;
			}
		}
	}
	
}

/////////////////////////////////////////////////////////////////////////
/////////////////////////  sort link list  //////////////////////////////
void sort_link_list(void){
	struct node *temp_h = head, *i, *j, *next_i, *min;;
    int temp;
    for(i = temp_h; i!=NULL && i->next!=NULL; i=i->next){
        min = i;
        for(j = i->next; j!=NULL ; j=j->next){
            if(j->value < min->value)
                min=j;
        }
        if(min != i){
            temp = min->value;
            min->value = i->value;
            i->value = temp;
        }
    }
    head = temp_h;
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
