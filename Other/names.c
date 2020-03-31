/* Takes a string as input and prints the reverse */

#include<stdio.h>
#include<ctype.h>
#define MAX 20 
int main(void) {
	char name[MAX], temp;
	int len = 0;
	
	printf("Enter your name: ");
	scanf("%s", name);
	
	while(name[len]!='\0'){
		len++;
	}
	//printf("%d", len);
	//printf("The revere is: %s\n", name);
	
	for(int i = len; i >= 0; i--){
		printf("%c", tolower(name[i]));
	}
		
	return 0;
}