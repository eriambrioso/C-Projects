/* Implements quicksort on an array of 10 items */
/* This code could be changed to accept larger inputs
    or to generate its own input... */

#include<stdio.h>
#include<stdlib.h>
 
void swap(int* a, int* b);
int divide (int array[], int min, int max);
void quick_sort(int array[], int min, int max);
void print_array(int array[], int size);

int main(void){
    int array[10];
	printf("Enter 10 numbers: \n");
	for(int i =0; i < 10; i++){
		scanf("%d", &array[i]);
	}
	// min is 0 and max is 10
    quick_sort(array, 0, 10);
	
	printf("The sorted array: ");
    print_array(array, 10);
	
	
    return 0;
}

int divide (int array[], int min, int max){
    int pivot = array[max];    // always start the pivot at the highest index value(max)
    int i = (min-1); // left pointer
 
    for (int j = min; j <= max- 1; j++){
        if (array[j] <= pivot){		//if value belongs below the pivot 
            i++;    
            swap(&array[i], &array[j]);  // swap the addresses of the 
        }
    }
    swap(&array[i + 1], &array[max]);
    return (i + 1);
}
void quick_sort(int array[], int min, int max){
    if (min < max){
        int div = divide(array, min, max);
 
        quick_sort(array, min, div - 1);		// lower half
        quick_sort(array, div + 1, max);		// upper half

    }
}


void swap(int* a, int* b){	// swaps the addresses of two int variables
    int temp;
	temp = *a;
    *a = *b;
    *b = temp;
}
void print_array(int array[], int size){
    for (int i = 0; i < size; i++){
        printf("%d ", array[i+1]);
	}
    printf("\n");
}
 