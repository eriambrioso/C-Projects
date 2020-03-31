#include<stdio.h>

void print_array(int size, double array[]);
double calculate_distance(int n, double cap, double rate, double max);

int main(void){
	int n, count = 0;										// count keeps track of number of outputs
	double cap, rate, max;									
	double output[1000];									// output holds all the final calculations
	
	scanf("%d", &n);
	while(n != 0){														
		max = 0;
		scanf("%lf %lf", &cap, &rate);
		max = calculate_distance(n, cap, rate, max);	
		output[count] = max;							
		count++;
		
		scanf("%d", &n);
	}
	
	print_array(1000, output);

	return 0;
}
double calculate_distance(int n, double cap, double rate, double max){
	n = n - 1;
	double one_can = (cap/rate) * 100;
	double temp_n = 2*(n-1) + 1;
	double total = 0, distance;
	for(int i = 1; i < n + 1; i++){
		temp_n = 2*(n - i) + 1;
		printf("%.0lf ", temp_n);
		distance = 1/temp_n;
		total = total + distance;
		printf("%lf %lf\n", distance, total);
	}
	total = (total + 1) * one_can;
	return total;
}


void print_array(int size, double array[]){
	int i = 0;										
	while(array[i] != '\0'){
		printf("%d. Distance is: %.2lf\n", i+1, array[i]);			
		i++;
	}
}