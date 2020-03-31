/* 
 * Author: Erika Ambrioso, eambrioso2017@my.fit.edu 
 * Course: CSE 2010, Section 4; Fall 2018 
 * Assignment:hw1
 * Description: The program recieves an input file of customer chat request, and determines
   if the cutomer can be matched with a representative or placed on hold. The output is printed
   to the screen
 */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <stdbool.h>

typedef struct REP {					// holds the avaible representatives
	char name[100];
	struct REP *next;
} REP;
 
typedef struct CHATS {					// holds all the chat requests and the info about them
	int start_time;
	char customer;
	int length;								// original length given as input
	int length_edit;						// edited length
	char will_wait[100];
	REP *assigned_rep;					// the rep that is assigned to the customer
	struct CHATS *next;
} CHATS;

int max_wait = 0;						// global variable for max wait time
CHATS *wait_head = NULL;				// head pointers
CHATS *chat_head = NULL;
REP *reps_head = NULL;

/* fuctions ***********************************************************/
void update_time(int time);
void time_check(int time);
void new_chat(CHATS *chat);
void put_on_hold(CHATS *chat);
void add_rep(char _name[100]);
REP *assign_rep();
void take_off_hold(char remove);
void print_available_reps(int time);

int av_rep_count();				// counting functions
int finished_count();
int hold_count();
int chats_count();

 
int main(int argc, char *argv[]){						/******* MAIN STARTS HERE *******/
	FILE *fp = fopen(argv[1], "r"); 	//fp-->file pointer
	int time = -1, e_time = -1;							// input is the input line that is tokenized
	char input[100], command[100], input_line[100];		// input_line is the entire input line, unedited

	add_rep("Alice");					// initial state: all reps are available
	add_rep("Bob");
	add_rep("Carol");
	add_rep("David");
	add_rep("Emily");
	while(fgets(input, 100, fp)) {					
		strcpy(input_line, input);						// copy entire line into the two strings
		char *token = strtok(input, " ");				// toeknize the input using " "
		strcpy(command, token);
		token = strtok(NULL, " ");
		if(e_time < 0) {								// if first line
			e_time = atoi(token);
			time = e_time;
		} else {		
			e_time = time;			
			time = atoi(token);
		}
		update_time(time - e_time);
		time_check(time - e_time);
		if(strcmp(command, "ChatRequest") == 0) {
			printf("%s", input_line);

				CHATS *temp = (CHATS *) malloc(sizeof(CHATS));				// create new node
				char *token = strtok(input_line, " ");
				token = strtok(NULL, " ");									// tokenize the input...
				temp->start_time = atoi(token);
				token = strtok(NULL, " ");
				temp->customer = token[0];
				token = strtok(NULL, " ");
				temp->length_edit = atoi(token);
				temp->length = temp->length_edit;
				token = strtok(NULL, " ");
				strcpy(temp->will_wait, token);
				temp->assigned_rep = assign_rep();							// call function to assign a rep
				temp->next = NULL;											// add the pointer

			if(temp->assigned_rep != NULL) {
				printf("RepAssignment %c %s %04d\n", temp->customer, temp->assigned_rep->name, temp->start_time);
				new_chat(temp);
			} 
			else {															// if there are no av. reps, put on hold
				if(temp->will_wait[0] == 'w') {
					printf("PutOnHold %c %04d\n", temp->customer, temp->start_time);
					put_on_hold(temp);
				} 
				else {
					printf("TryLater %c %04d\n", temp->customer, temp->start_time);
				}
			}
		}
		else if(strcmp(command, "PrintAvailableRepList") == 0) {
			print_available_reps(atoi(token));
		}
		else if(strcmp(command, "QuitOnHold") == 0) {
			printf("%s", input_line);
			token = strtok(NULL, " ");
			take_off_hold(token[0]);
		}
		else if(strcmp(command, "PrintMaxWaitTime") == 0) {
			printf("MaxWaitTime %04d %d\n", atoi(token), max_wait);
		}
		else{
			printf("ERROR: Invalid Command\n");
		}
	}
	update_time(1000);
	time_check(1000);
	
	fclose(fp);
}
/* update the time for all open chat requests *******************************/
/* subtracts the time that has passed from the length of the chat left */
void update_time(int time) {
	CHATS *temp = chat_head;
	while(temp != NULL) {
		temp->length_edit -= time;
		temp = temp->next;
	}
}
/* determines which chat is ending, prints hte output in correct order ***************************/
void time_check(int delta) {
	while(finished_count() > 0) {		
		CHATS *recent = chat_head, *current = chat_head;
		int i = -1, time = 0, e_time = 0, count = 0;
				
		while(current != NULL) {		// if projected end_time sooner than the prev. recent and chat is over change recent to current
			if((current->start_time + current->length) <= (recent->start_time + recent->length) && current->length_edit <= 0 ) {
				recent = current;
				i = count;				// i represents the index of the recent
			}
			count++;
			current = current->next;
		}
		e_time = recent->start_time + recent->length;				// projected end time of recent
		printf("ChatEnded %c %s %04d\n", recent->customer, recent->assigned_rep->name, e_time);		// end the chat
		add_rep(recent->assigned_rep->name);														// make rep available
		recent->assigned_rep = NULL;
		CHATS *temp = recent;
		
		if(i == 0) {					// if its at the head
			chat_head = recent->next;
			recent->next = NULL;
		} else {
			CHATS *last = chat_head;
			while(i - 1 > 0) {			// traverse through the list
				last = last->next;
				i--;
			}
			last->next = recent->next;			// remove it from the list by adjusting the pointers
		}
		recent->next = NULL;
		time = recent->start_time + recent->length;
		free(recent);
		
		if(av_rep_count() > 0 && hold_count() > 0) {			// check if theres an avaible rep and if theres someone on hold
			CHATS *temp = wait_head;
			wait_head = wait_head->next;
			temp->assigned_rep = assign_rep();					// assign rep to customer on hold
			if((time - temp->start_time) > max_wait) {
				max_wait = (time - temp->start_time);
			}
			temp->start_time = time;
			temp->length_edit = temp->length_edit - delta;
			temp->next = NULL;
			new_chat(temp);										
			printf("RepAssignment %c %s %04d\n", temp->customer, temp->assigned_rep->name, temp->start_time);
		}
	}
}
/* adds a node to the end of the chat list ****************************************/
void new_chat(CHATS *chat) {
	CHATS *temp = chat_head;

	if(chat_head == NULL) {				// if this is the first chat...
		chat_head = chat;
		return;
	}
	while(temp->next != NULL) {
		temp = temp->next;
	}
	temp->next = chat;
}
/* add a customer to the hold list ***************************************************/
/* recieves customer to put on hold */
void put_on_hold(CHATS *chat_to_hold) {
	CHATS *temp = wait_head;

	if(wait_head == NULL) {					// if the list is empty
		wait_head = chat_to_hold;
		return;
	}
	while(temp->next != NULL) {
		temp = temp->next;					// traverse to end of list
	}
	temp->next = chat_to_hold;
}
/* adds rep to end of list *************************************************************/
/* when a rep becomes avaible they are added to av. rep list. 
	takes the reps name as input*/
void add_rep(char _name[100]) {
	struct REP *temp = (REP *) malloc(sizeof(REP));			// allocate the memory for the new node
	strcpy(temp->name, _name);					
	temp->next = NULL;
	
	if(reps_head == NULL) {						// if empty
		reps_head = temp;
	} 
	else { 
		REP *temp2 = reps_head;
		while(temp2->next != NULL) {			// traverse to the end with temp2and point to the new node
			temp2 = temp2->next;
		}
		temp2->next = temp;
	}
}
/* removes a customer from the waiting list ********************************************/
void take_off_hold(char remove) {		
	CHATS *temp = wait_head;		
	if(wait_head->customer == remove) {		// if customer is at the begining adjust the head pointer...
		wait_head = wait_head->next;
		free(temp);
		return;
	}
	while(temp != NULL) {
		if(temp->next->customer == remove) {			
			CHATS *temp2 = temp->next;		// create temp2 which is used to free the node after its removed
			temp->next = temp2->next;
			temp2->next = NULL;
			free(temp2);
			return;
		}
		temp = temp->next;					// traverse through the list to find the customer using temp
	}
}

/* counts the number of avaible reps and returns the value ***********************************/
int av_rep_count() {
	REP *temp = reps_head;			// temp is used to traverse through list
	int count = 0;					// count keeps track of av. reps
	while(temp != NULL) {
		count++;
		temp = temp->next;
	}
	return count;
}
/* counts the number of customers on hold and returns the value *********************************/
int hold_count() {
	int count = 0;
	CHATS *temp = wait_head;			// use temp to traverse throught the list
	while(temp != NULL) {
		count++;
		temp = temp->next;
	}
	return count;
}
/* counts the chats that are completed and returns the value ************************************/
int finished_count() {
	int count = 0;
	CHATS *temp = chat_head;
	while(temp != NULL) {
		if(temp->length_edit <= 0) {				// checks if the chat has lasted the full duration
			count++;
		}
		temp = temp->next;
	}
	return count;
}
/* counts all chats in the chat list and returns the value ***************************************/
int chats_count() {
	int count = 0;
	CHATS *temp = chat_head;				// use temp to traverse thorugh the list
	while(temp != NULL) {
		count++;
		temp = temp->next;
	}
	return count;
}
/* returns rep to be assigned ***************************** *********************************/
/* returns head of the list and NULL if the list is empty */
REP *assign_rep() {
	REP *temp = reps_head;

	if(av_rep_count() == 0) {		// if there are no avaible reps, the customer should be put on hold
		return NULL;
	}
	reps_head = reps_head->next;	// otherwise return the rep at the head
	temp->next = NULL;
	return temp;
}

/* prints the avaiable representatives if any **********************************************/
/* prints nothing if their are no reps avaiable */
void print_available_reps(int time) {
	REP *temp = reps_head;						// temp is used to traverse through the list

	printf("AvailableRepList %04d ", time);
	if(reps_head != NULL){
		while(temp->next != NULL) {
			printf("%s ", temp->name);
			temp = temp->next;	
		}
		printf("%s ", temp->name);
	}
	printf("\n");
}
