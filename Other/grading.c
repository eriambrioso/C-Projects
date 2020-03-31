/* User can input 10 number grades. The output will be the min, max,
   average grade, and the standard deviation*/

#include<stdio.h>
#include<math.h>

int main(void) {
	int grades[10], min, max;
	double average, std_dev;
	
	for(int i = 0; i < 10; i++){
		printf("Enter a grade---> ");
		scanf("%d", &grades[i]);
	}
	
	//find min, max, and average
	min = grades[0];
	max = grades[0];
	average = 0;
	
	for(int j = 0; j < 10; j++) {
		average += grades[j];
		if(grades[j] < min) {
			min = grades[j];
		}
		if(grades[j] > max) {
			max = grades[j];
		}
	}
	average /= 10;

	printf("The minimum value is %d\n", min);	
	printf("The maximum value is %d\n", max);
	printf("The average value is %lf\n", average);
	
	//find SD
	std_dev = 0;
	for(int k = 0; k < 10; k++) {
		std_dev = std_dev + (pow((grades[k] - average), 2));
	}
	std_dev = sqrt(std_dev / 10);
	printf("The standard deviation is %lf\n", std_dev);
	
	return 0;
}