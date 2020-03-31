/* Will accept 3 integers as input and print the prime factors of each */
#include<stdio.h>
#include<math.h>

void prime_factors(int x);
void direct_search(int y);

int main(void) {
	int num1, num2, num3;
	
	printf("Enter three integers---> ");
	scanf("%d %d %d", &num1, &num2, &num3);
	prime_factors(num1);
	prime_factors(num2);
	prime_factors(num3);
	return 0;
}

void prime_factors(int x){
	int prime;
	printf("The prime factors of %d are: ", x);
	for(int i = 1; i <= x ;i++){
		prime = 1;
		if (x % i == 0) {
			for(int k = 2; k < i; k++) {
				if(i % k == 0) {
					prime = 0;
				}
			}
			if(prime == 1) {
				printf("%d ", i);
			}
		}
	}
	printf("\n");
}

		
		
		
		
		
		
		
		
		
		
		
		
	