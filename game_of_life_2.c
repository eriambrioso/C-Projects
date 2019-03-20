/* 
 * Author: Erika Ambrioso, eambrioso2017@my.fit.edu 
 * Course: CSE 1002, Section 01/02, Spring 2018 
 * Project: game_of_life_2
 */

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <unistd.h>


#define MAX 100

int get_size(char filename[MAX]);
void read_file(char filename[MAX],int lines, int col, int gen1[lines][col]);
int check_neighborhood(int lines, int col, int i, int j, const int gen1[lines][col]);
void create_gen2(int lines, int col, int gen1[lines][col], int gen2[lines][col]);
void run_game(int lines, int col, int gen1[lines][col], int gen2[lines][col], int its);
void save_file(int lines, int col, int gen2[lines][col]);

int main(int argc, char **argv) {
	int lines = get_size(argv[1]);					// get the size
	int iterations = atoi(argv[2]);
	int gen1[lines][lines], gen2[lines][lines];		// generation one and generation 2
	
	read_file(argv[1], lines, lines, gen1);			// read into array
	run_game(lines, lines, gen1, gen2, iterations);
	save_file(lines, lines, gen2); 					// save to output file
	return 0;
}


int get_size(char filename[MAX]){
	FILE *f1 = fopen(filename, "r");
	char check;
	int lines = 0;
	while((check = fgetc(f1)) != EOF){			//count the number of '\n' to get number of lines
		if (check == '\n'){
			lines++;						
		}
	}
	fclose(f1);
	return lines;
}
void read_file(char filename[MAX],int lines, int col, int gen1[lines][col]){
	FILE *f1 = fopen(filename, "r");
	char check, value;
	int i=0, j=0;								// i represents rows and j represents columns
	
	while((check = fgetc(f1)) != EOF){			// only put 0's and 1's into the array
		if (check == '0'){
			gen1[i][j] = 0;
			j++;
		}
		if (check == '1'){
			gen1[i][j] = 1;
			j++;
		}
		if (check == '\n'){
			i++;
			j=0;
		}
	}
	
	
	fclose(f1);
}
void save_file(int lines, int col, int gen2[lines][col]){	
	FILE *f2 = fopen("output.csv", "w");
	for(int i =0; i < lines; i++){
		for(int j = 0; j <col; j++){
			if(j == col-1){
				fprintf(f2, "%d\n", gen2[i][j]);
			}
			else{
				fprintf(f2, "%d;", gen2[i][j]);
			}
		}
	}
	
	fclose(f2);
}
void create_gen2(int lines, int col, int gen1[lines][col], int gen2[lines][col]){
	int live_neighbors=0;
	for(int i = 0; i < lines; i++){
		for(int j = 0; j < col; j++){
			live_neighbors=check_neighborhood(lines, col, i, j, gen1);
			if (gen1[i][j]==1){
				if (live_neighbors == 2 || live_neighbors==3){
					gen2[i][j] = 1;
				}else{
					gen2[i][j]=0;
				}
			}
			if (gen1[i][j]==0){
				if (live_neighbors==3){
					gen2[i][j] = 1;
				}else{
					gen2[i][j] = 0;
				}
			}
		}
	}
}
void run_game(int lines, int col, int gen1[lines][col], int gen2[lines][col], int its){
	for(int i = 0; i < its + 1; i++){			// its---> iterations
		sleep(2);
		system("clear");
		create_gen2(lines, lines, gen1, gen2);
		if(i == 0){
			printf("input\n");							// the first print will be the input
		}
		else {
			printf("iteration %d\n", i);
		}
		for(int k = 0; k < lines; k++){
			for(int m =0; m < col;m++){
				if(gen1[k][m] == 0){
					printf("  ");
				}
				else if(gen1[k][m] == 1){
					printf(" *");
				}
			}
			printf("\n");
		}
		
		for(int j =0; j < lines; j++){					// set gen2 to gen1 before running next iteration
			for(int k = 0; k <lines; k++){	
				gen1[j][k] = gen2[j][k];
			}
		}
	}
}
int check_neighborhood(int lines, int col, int i, int j, const int gen1[lines][col]){
	int live = 0;										//live is the number of living neighbors
	
	if (i > 0){
		if (j<col){
			if(gen1[i-1][j+1] == 1){
				live++;
			}
		}
		if(gen1[i-1][j] == 1){
			live++;
		}
		if(j>0){
			if(gen1[i-1][j-1] == 1){
				live++;
			}
		}

	}
	if (i<lines){
		if(gen1[i+1][j] == 1){
			live++;
		}	
		if(j>0){
			if(gen1[i+1][j-1] == 1){
				live++;
			}
		}
		if(j<col){
			if(gen1[i+1][j+1] == 1){
				live++;
			}
		}
	}
	if(j<col){
		if(gen1[i][j+1] == 1){
			live++;
		}
	}
	if(j>0){
		if(gen1[i][j-1] == 1){
			live++;
		}
	}
	return live;
}
