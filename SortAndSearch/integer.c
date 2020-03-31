#include<stdio.h>
#include<string.h>

void scan_numbers(int size, int numbers[]);
void print_numbers(int size, int numbers[]);
void selection_sort(int numbers[], int size);
void swap(int *x_p, int *y_P);

int main(void){
	int size;
	
	printf("Enter the size of the array---> ");
	scanf("%d", &size);
	
	int numbers[size];
	
	printf("Enter the numbers---> ");
	scan_numbers(size, numbers);
	selection_sort(numbers, size);
	print_numbers(size, numbers);
	
	return 0;
	
}

//8 4 7 2 3

void selection_sort(int numbers[], int size){
	int min = numbers[0], position = 0;
	for(int j = 0; j < size; j++){
		min = numbers[j];
		for(int i = j; i < size; i++){
			if(numbers[i] < min){
				min = numbers[i];
				position = i;
			}
		}
	swap(&numbers[position], &numbers[j]);
	}
	
}

void swap(int *x_p, int *y_p){
	int temp = *x_p;
	*x_p = *y_p;
	*y_p = temp;
}

void scan_numbers(int size, int numbers[]){
	for(int i = 0; i < size; i++){
		scanf("%d", &numbers[i]);
	}
}
void print_numbers(int size, int numbers[]){
	printf("The sorted array is---> ");
	for(int i = 0; i < size; i++){
		printf("%d ", numbers[i]);
	}
}