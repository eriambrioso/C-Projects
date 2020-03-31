/* User enters an ammount of money and program outputs
   how many of each bill should be given.
*/
/*******MUST ADD $5 AND $1 BILLS**************/
#include<stdio.h>

void dispense(int, int*, int*, int*);

int main(void) {
	int total_money, fifty = 0, twenty = 0, ten = 0;
	
	printf("Enter the ammount of money---> ");
	scanf("%d", &total_money);
	
	dispense(total_money, &fifty, &twenty, &ten);
	
	printf("Number of $50 bills: %d\n", fifty);
	printf("Number of $20 bills: %d\n", twenty);
	printf("Number of $10 bills: %d\n", ten);

	return 0;
}

void dispense(int m, int *fifty_p, int *twenty_p, int *ten_p) {
	*fifty_p = m / 50;
	m = m % 50;
	*twenty_p = m / 20;
	m = m % 20;
	*ten_p = m / 10;
}