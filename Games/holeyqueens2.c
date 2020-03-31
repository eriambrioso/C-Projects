/* Descrption: The n-queens problem is figuring out how to place n queens on an nxn chess board so
   that no queencan attack another. The holey n queens problem is the same problem howvere there are 
   holes on the board which a queen can pass through but not be placed on.
   
   This code take the size of the board, the number of holes, and the postion of each hole (as an xy pair)
   as input and outputs the number of soltuions to the "holey n-queens problem"

   The program will end if the user inputs 0 0
*/

#include<stdio.h>
#include<stdlib.h>
#define MAX 12


int solution_count(int size, int board[MAX][MAX], int row);
void add_holes(int size, int board[MAX][MAX], int row, int col);
void copy_array(int size, int source[MAX][MAX], int dist[MAX][MAX]);

int main(void) {
	int size, num_holes = 0, x, y, solutions, row, total;
	scanf("%d %d", &size, &num_holes);
	int board[MAX][MAX];
	
	while(size != 0){									// while loop to repeat until 0 0 is inputed
		solutions = 0;
		row = 0;
		total = 0;
	
		for(int j = 0; j < size; j++){					// initialize board to 0
			for(int k = 0; k < size; k++){
				board[j][k] = 0;
			}
		}
														
		for(int i = 0; i < num_holes; i++){				// add holes from input
			scanf("%d %d", &x, &y);
			board[x][y] = 1;
		}
		
		total = solution_count(size, board, row);		/*solution count is recursive and will 
														ultimtely return the total number of 
														solutions the input will result in*/
		printf("%d\n", total);
		scanf("%d %d", &size, &num_holes);				// gets the new values for the next case	
		
	}

	return 0;
}

int solution_count(int size, int board[MAX][MAX], int row){			//returns # of solutions
	int temp_board[MAX][MAX];
	int solutions=0, num_open = 0;
	
	for(int l = 0; l < size; l++){
		if(board[row][l] == 0){					// num_open: the # of open squares in the given row(l)
			num_open++;
		}
	}
	/*2 base cases: when a queen cannot be placed in a row 
	or the program reaches the final row of the board*/
	if(num_open == 0){							
		return 0;
	}
	else if(row == size-1){						
		return num_open;
	}
	else{
		/*for each square in the row, if square is 0(open) create a temporary board in order to maintain
		the original positions. Add a queen to the temp board and add 1's to spaces that the queen will 
		attack. Then run the temp board through the recursion*/
		/**Each time solution_count is called a new temp_board is created and passed through the next recursion **/
		for(int i = 0; i < size; i++){				
			if(board[row][i] == 0){
				copy_array(size, board, temp_board);	
				add_holes(size, temp_board, row, i);
				solutions = solutions + solution_count(size, temp_board, row+1);		// recursion :o
					
			}

		}
		return solutions;
	}
}
/*** I am almost certain this is where the problem is ***/
void add_holes(int size, int board[MAX][MAX], int row, int col){	// puts holes in the squares queen attacks
	int temp_row = row, temp_col = col;

	while(row < size){							// while the next row is less than size add holes below
		board[row][col] = 1;
		row++;
	}
	row = temp_row;									// reset row and col to original input
	col = temp_col;	
	while(col < size && row < size){				// add holes rightward diagonal
		board[row][col] = 1;
		col++;
		row++;
	}
	row = temp_row;
	col = temp_col;
	while(col >= 0 && row < size){				// add holes leftward diagonal
		board[row][col] = 1;
		col--;
		row++;
	}
	row = temp_row;
	col = temp_col;

}	

void copy_array(int size, int source[MAX][MAX], int dist[MAX][MAX]){		//copies all values of the first array into the second
	for(int i = 0; i < size; i++){
		for(int j = 0; j < size; j++){
			dist[i][j] = source[i][j];
		}
	}
}
