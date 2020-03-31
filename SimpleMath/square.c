/* Accepts integers as input from user. Will print out the square and 
   the cube of each integer entered. */

#include<stdio.h>

int main(void){
	int length;
	int val_array[length];

	printf("How many values would you like to enter? ");
	scanf("%d", &length);
	
	for(int i = 0; i < length; i++) {
		printf("Enter a value---> ");
		scanf("%d", &val_array[i]);
	}
	
	//squares
	for(int j = 0; j < length; j++) {
		printf("%d, ", val_array[j] * val_array[j]);
	}
	printf("\n");
	//cubes
	for(int k = 0; k < length; k++) {
		printf("%d, ", val_array[k] * val_array[k] * val_array[k]);
	}	
	return 0;
}