#include<stdio.h>
#include<string.h>

int main(void){
	
	char string1[50], string2[50], string3[50], order[150];
	
	
	printf("Enter three strings---> ");
	scanf("%s %s %s", string1, string2, string3);

	if(strcmp(string1, string2) < 0 && strcmp(string1, string3) < 0) {
		strcpy(order, string1);
		strcat(order, " ");
		if(strcmp(string2, string3) < 0){
			strcat(order, string2);
			strcat(order, " ");
			strcat(order, string3);
		}
		else{
			strcat(order, string3);
			strcat(order, " ");
			strcat(order, string2);
		}
	}
	else if(strcmp(string1, string2) < 0 && strcmp(string1, string3) > 0){
		strcpy(order, string3);
		strcat(order, " ");
		strcat(order, string1);
		strcat(order, " ");
		strcat(order, string2);
	}
	else if(strcmp(string1, string2) > 0 && strcmp(string2, string3) < 0){
		strcpy(order, string2);
		strcat(order, " ");
		if(strcmp(string1, string3) < 0){
			strcat(order, string1);
			strcat(order, " ");
			strcat(order, string3);
		}
		else{
			strcat(order, string3);
			strcat(order, " ");
			strcat(order, string1);
		}
	}
	else if(strcmp(string1, string3) > 0 && strcmp(string2, string3) > 0){
		strcpy(order, string3);
		strcat(order, " ");
		if(strcmp(string1, string2) < 0){
			strcat(order, string1);
			strcat(order, " ");
			strcat(order, string2);
		}
		else{
			strcat(order, string2);
			strcat(order, " ");
			strcat(order, string1);
		}
	}
	printf("%s", order);
	return 0;
}