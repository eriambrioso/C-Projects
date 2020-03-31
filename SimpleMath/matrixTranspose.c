/* Prints the transpose a matrix.
   --user must input the size n*m and the values of the matrix 
*/
#include<stdio.h>

int main(void) {
	int row, col;
	
	printf("Enter Sizes---> ");
	scanf("%d %d", &row, &col);
	
	int matrix[row][col];
	printf("Enter Matrix---> ");

	for(int i = 0; i < row; i++){
		for(int j = 0; j < col; j++){
			scanf("%d", &matrix[i][j]);
		}
	}
	
	printf("Original: \n");
	for(int k = 0; k < row; k++){
		for(int l = 0; l < col; l++){
			printf("%d ", matrix[k][l]);
		}
		printf("\n");
	}

	printf("Transpose: \n");
	for(int m = 0; m < col; m++){
		for(int n = 0; n < row; n++){
			printf("%d ", matrix[n][m]);
		}
		printf("\n");
	}

	return 0;
}

