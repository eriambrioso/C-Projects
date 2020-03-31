/* Prints the nth term of the fibonacci sequence using
   a recursive method */

#include<stdio.h>

int fib(int n);

int main(void){
	int n;
	printf("Enter a value for n---> ");
	scanf("%d", &n);
	printf("The %d term in the fibonacci sequence is %d", n, fib(n));
	

	return 0;
}

int fib(int n){
	if( n == 0 || n == 1) {
		return 1;
	}
	return fib(n - 1) + fib(n - 2);
	
}