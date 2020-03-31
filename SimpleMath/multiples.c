/* accepts 3 integers as the input: base, lower limit, and upper limit.
   Finds all multiples of the base within the limit defined. */
#include<stdio.h>

void multiples(int base, int lower_limit, int upper_limit);

int main(void) {
	int end = 'n';
	int b, l, u;
	while(end != 'y') {	
		printf("Input the base, lower and upper limits---> ");
		scanf("%d", &b);
		scanf("%d", &l);
		scanf("%d", &u);
		multiples(b, l, u);
		printf("Do you want to end? y/n \n");
		scanf(" %c", &end);
	}

	return 0;
}

void multiples(int base, int lower_limit, int upper_limit) {

		for(int i = lower_limit; i <= upper_limit; i++) {
			if(i % base == 0) {
				printf("%d ", i);
			}
		}
}