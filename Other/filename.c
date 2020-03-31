/* Demonstration of parsing user input specfically a filepath and name */
#include<stdio.h>
#include<string.h>

int main(void) {
	char file_path[100];
	printf("Enter the file path---> ");
	scanf("%s", file_path);
	
	char *token = strtok(file_path, "./");

	while(token != NULL){
		printf("%s\n", token);
		token = strtok(NULL, "./");

	}
	return 0;
}