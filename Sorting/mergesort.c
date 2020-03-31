/* Implements merge sort on an array of 10 items 
	This program could be changed to handle larger or 
	varying input sizes */
	
#include<stdio.h>
#include<stdlib.h>

void m_sort(int array[], int p, int r);
void merge(int array[], int p, int q, int r);

int main(void){
	int array[10], p = 0, r = 9;
	// collect input and story in array
	printf("Enter an array of 10 items\n");
	for(int i = 0; i < 10; i++){
		scanf("%d", &array[i]);
	}
	// call the merge sort function 
	m_sort(array, p, r);
	// print the results
	printf("The sorted array:\n");
	for(int j = 0; j < 10; j++){
		printf("%d ", array[j]);
	}
	
	return 0;
}
/* recursive function to spilt the array */
void m_sort(int array[], int p, int r){
	int q;
	
	if(p < r){
		q = (p + r) / 2;
		m_sort(array, p, q);
		m_sort(array, q+1, r);
		
		merge(array, p, q, r);
	}
}
/* called by m_sort, this is the step of the recursion that rebuilds the array
	from the subarrays */
void merge(int array[], int p, int q, int r){
	int size1 = (q-p)+1, size2 = r-q;	// sizes of temp arrays
	//printf("size1:%d size2=%d\n", size1, size2);
//	printf("p:%d q=%d r=%d\n", p, q, r);

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
	//printf("\n");
	
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