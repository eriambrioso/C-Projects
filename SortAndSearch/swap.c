/* Simple example of swapping the values of variables using pointers */

    #include <stdio.h>

int main(void) {
    int number_1, number_2;
    printf("Enter two numbers\n");
    scanf("%d %d", &number_1, &number_2);

    printf("Before\n");
    printf("number_1 = %d\n", number_1);
    printf("number_2 = %d\n", number_2);
    
    int *number_1_p = &number_1;
    int *number_2_p = &number_2;
	
    // Code swapping the values of number_1 and number_2 using their pointers 
	int temp1 = number_1;
	*number_1_p = number_2;
	*number_2_p = temp1;	
    
    
    // swapping code ends here
    printf("After\n");
    printf("number_1 = %d\n", number_1);
    printf("number_2 = %d\n", number_2);
}