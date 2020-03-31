/*
	to compile use gcc merge_v_quick.c -o merge_v_quick
	to run use ./merge_v_quick "mvq.csv" "mvq2.csv"
*/

/* Erika Ambrioso
	CSE2010
	Assignment 6b 
	Compares a merge sort and a quick sort algorithm using file input
	**the first file to run with is "mvq.csv" which hass approx 400 random unsorted numbers
	**the second file to run with is "mvq2.csv" which has approx 400 almost sorted numbers
	
*/

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<unistd.h>

#define MAX_IN 10000
 
void swap(int* a, int* b);
int divide (int array[], int min, int max);
void quick_sort(int array[], int min, int max);
void print_array(int array[], int size);
void m_sort(int array[], int p, int r);
void merge(int array[], int p, int q, int r);

int get_size(char filename[MAX_IN]);

int main(int argc, char **argv){
	int size = get_size(argv[1]);				
	int array_q[size], array_m[size];				// the input array
	double q_time, m_time;
	clock_t startt, endt;			// used to keep track of timing
	srand(time(0));
	
	FILE *f1 = fopen(argv[1], "r");
	FILE *f2 = fopen(argv[2], "r");
	for(int i = 0; i <size; i++){			// put everythinig from the file into the arry 
		fscanf(f1, "%d,", &array_q[i]);
		array_m[i] = array_q[i];
	}
	startt = clock();
	printf("START: %d ", startt);
	m_sort(array_m, 0, size-1);				// call merge sort
	//print_array(array_m, size);
	endt = clock();
	printf("END: %d\n", endt);
	m_time = ((double)(endt - startt))/ CLOCKS_PER_SEC;
	
	startt = clock();
    quick_sort(array_q, 0, size);				// min is 0 and max is size for the first call of q_sort
	endt = clock();
	q_time = ((double)(endt-startt))/CLOCKS_PER_SEC;
	
	printf("Quick sort took %d time and merge sort took %d time on unsorted list\n", q_time, m_time);
	
	// do it again on sorted list
	
	size = get_size(argv[2]);
	for(int j = 0; j <size; j++){			// put everythinig from the file into the arry 
		fscanf(f2, "%d,", &array_q[j]);
		array_m[j] = array_q[j];
	}
	
		startt = 0;
	m_sort(array_m, 0, size-1);				// call merge sort
	endt = 0;
	m_time = endt-startt;
	
	startt = 0;
    quick_sort(array_q, 0, size);				// min is 0 and max is size for the first call of q_sort
	endt = 0;
	q_time = endt-startt;
	
	
	printf("Quick sort took %.2f time and merge sort took %.2f time on a partially sorted list\n", q_time, m_time);

	fclose(f1);
	fclose(f2);
}
// used in quick sort to break down the array
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
//recursively calls itself and does a comparison
void quick_sort(int array[], int min, int max){
    if (min < max){
        int div = divide(array, min, max);
 
        quick_sort(array, min, div - 1);		// lower half
        quick_sort(array, div + 1, max);		// upper half

    }
}
// used in quick_sort when a comparsionn is made and value need to be swapped
void swap(int* a, int* b){	// swaps the addresses of two int variables
    int temp;
	temp = *a;
    *a = *b;
    *b = temp;
}
// simple print of a standard array
void print_array(int array[], int size){
    for (int i = 0; i < size; i++){
        printf("%d ", array[i+1]);
	}
    printf("\n");
}
// merge sort function, p is start index and r is the end index
void m_sort(int array[], int p, int r){
	int q;
	
	if(p < r){
		q = (p + r) / 2;
		m_sort(array, p, q);
		m_sort(array, q+1, r);
		
		merge(array, p, q, r);
	}
}
// used in the merge sort function to combine the broken down array
void merge(int array[], int p, int q, int r){
	int size1 = (q-p)+1, size2 = r-q;	// sizes of temp arrays

	int i, j, k = p;					// counters for loops
	int m1_array[size1], m2_array[size2];
	
	for(i = 0; i < size1; i++){			// puts values in temp arrays
		m1_array[i] = array[p+i];
	}
	for(j = 0; j < size2; j++){
		m2_array[j] = array[q+1+j];
	}

	
	for(j = 0; j < size1; j++){
		//printf("%d ", m1_array[j]);
	}
	//printf("\n");
	
	for(j = 0; j < size2; j++){
		//printf("%d ", m2_array[j]);
	}
	
	i = 0; // counter for m1_array
	j = 0; // counter for m2_array
	
	while(i < size1 && j < size2){				// find the lower value and assign to the next position of final array
		if(m1_array[i] < m2_array[j]){
			array[k] = m1_array[i];
			i++;
		}
		else{
			array[k] = m2_array[j];
			j++;
		}
		k++;
	}
	
	while(i < size1){
		array[k] = m1_array[i];
		i++;
		k++;
	}
	while(j < size2){
		array[k] = m2_array[j];
		j++;
		k++;
	}
	
	for(int j = 0; j < 5; j++){
		//printf("%d ", array[j]);
	}
}
// get the size of the input file
int get_size(char filename[MAX_IN]){
	FILE *f1 = fopen(filename, "r");
	char check;
	int size = 0;
	while((check = fgetc(f1)) != EOF){			//count the number of '\n' to get number of lines
		if (check == ','){
			size++;						
		}
	}
	fclose(f1);
	return size;
}
 