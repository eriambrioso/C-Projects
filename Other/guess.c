/* very simple guesssing game. The computer will pick a 4 letter word and the user
   tries to guess the letters of the word. */

#include<stdio.h>
#include<string.h>

int check_guess(char guess, const char my_word[]);
int main(void) {
	char my_word[] = "ball", guess;
	int try_num = 1, correct = 0;
	printf("I have a word with a length of 4\n"); 

	while(try_num <= 10 && correct < 4) {
		printf("Try number %d ---------------\n", try_num);
		printf("Guess a character in the word: ");
		scanf(" %c", &guess);
		if(check_guess(guess, my_word) == 1){
			printf("That's correct!\n\n");
			correct++;
		}
		else{
			printf("No sorry, guess again.\n\n");
		}
		try_num++;
	}

	printf("The word was ball");

	return 0;
}

int check_guess(char guess, const char my_word[]){
	int check = 0;
	for(int i = 0; i < 4; i++){
		check = 0;
		if(guess == my_word[i]){
			check = 1;
			break;
		}
	}
	return check;
}