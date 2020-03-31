/* Prints the union of two arrays */

#include<stdio.h>

int set_union(const int arr_1[], const int arr_2[], int arr_3[], int len);
void scan_1(int arr_1[], int len);
void scan_2(int arr_2[], int len);

int main (void) {
	int length;

	printf("What is the length of the array?");
	scanf("%d", &length);

	int array_1[length];
	int array_2[length];
	int array_3[length];
	
	printf("Enter array 1---> ");
	scan_1(array_1, length);

	printf("Enter array 2---> ");
	scan_2(array_2, length);

	printf("The union of the two arrays is: ");
	set_union(array_1, array_2, array_3, length);

	return 0;
}

int set_union(const int arr_1[], const int arr_2[], int arr_3[], int len){
	int found = 0, count = 0;
	for(int i = 0; i < len; i++) {
		arr_3[count] = arr_1[i];
		count++;
	}
	for(int j = 0; j < len; j++) {
		found = 0;
		for(int m = 0; m < len; m++){
			if(arr_2[j] == arr_3[m]){
				found = 1;
			} 
		}
		if(found == 0){
			arr_3[count] = arr_2[j];
			count++;
		}
	}

	for(int k = 0; k < count; k++){
		printf("%d ", arr_3[k]);
	}
	return 0;
}
void scan_1(int arr_1[], int len) {
	for(int i = 0; i < len; i++) {
		scanf("%d", &arr_1[i]);
	}
}
void scan_2(int arr_2[], int len) {
	for(int i = 0; i < len ;i++) {
		scanf("%d", &arr_2[i]);
	}
}