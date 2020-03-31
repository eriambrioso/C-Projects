/* Naive method of adding two integers by only add 1 at a time */

#include<stdio.h>
#include<string.h>

int naive_add(int n, int m);

int main(void){
	int m, n;
	printf("Enter the two integers---> ");
	scanf("%d %d", &n, &m);
	printf("The sum of %d and %d is %d", n, m, naive_add(n, m));

	return 0;
}

int naive_add(int n, int m){
	if(m == 1){
		return n + 1;
	}
	return 1 + naive_add(n, m - 1);
}