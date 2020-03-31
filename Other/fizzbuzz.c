/* A silly program that prints takes 3 integers as input: x, y, and max.
   The program counts from 1 to the max and prints "fizz" if a multiple of x,
   "buzz" if a multiple of y, and "FizzBuzz" if a multiple of both x and y. */

#include<stdio.h>
#include<math.h>

int main(void){
	int x, y, max;
	printf("Enter 3 integers x, y, and max: ");
	scanf("%d %d %d", &x, &y, &max);
	
	for(int i = 1; i <= max; i++){
		if((i%x) == 0 && (i%y) == 0) {
			printf("FizzBuzz\n");
		}		
		else if((i%x) == 0){
			printf("Fizz\n");
		}
		else if((i%y) == 0){
			printf("Buzz\n");
		}
		else{
			printf("%d\n", i);
		}
	}



	return 0;
}