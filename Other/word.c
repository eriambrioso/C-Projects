/* Searches for a specified word in a body of text. The 
   program will print the position the word is found */
#include<stdio.h>
#include<string.h>

int length(const char string[]);

int main(void){
	char str_line[400], key[10];
	int len = 0, k_len = 0, position = 1;
	
	printf("Enter some text---> ");
	gets(str_line);
	printf("Enter search key---> ");
	scanf("%s", key);
	
	len = length(str_line);
	k_len = length(key);
	
	for(int i = 0; i < len; i++){
		if(str_line[i] == ' '){
			position++;
		}
		if (strncmp(key, &str_line[i], k_len) == 0) {
			printf("The search key '%s' was found at position %d\n", key, position);
		}
	}

	return 0;
}

int length(const char string[]){
	int len = 0;
	while(string[len] != '\0') {
		len++;
	}
	return len;
}