/* approximates the value of pi and compares it to the actual value.
   The method for approximation calledd the Monte Carlo method.
   The more points you add the smaller the error will be. */
#include<stdio.h>
#include<math.h>
#define M_PI 3.14159265358979323846

int main(void){
	double points, in_points, calculated = 0, error, x,y;
	
	printf("Enter the number of points: ");
	scanf("%lf", &points);
	srand(time(0))
	
	for(int i = 0; i < points; i++){
		x = rand();
		y = rand();
		if(pow(x, 2)) + pow(y, 2) < 1){
			in_points++;
			calculated = calculated + (4* x/y);
			
		}
	}
	
	error = fabs(M_PI-error);
	
	
	printf("Inside points: %d\n", in_points)
	printf("Calculated value of Pi: %d\n", calculated);
	printf("The error is: %d", error);
	
	return 0;
}