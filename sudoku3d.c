#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Declare printSudoku function
void printSudoku(int***);
// Declare solveSudoku function
int solveSudoku(int***);


//Helper functions. You can define any functions that can help your solve the problem

bool isAvaliable(int ***arr, int block, int row, int column) {
	if (*(*(*(arr + block) + row) + column) == 0) {
		return true;
	}
	return false;
}

int rowBegin(int block) {
    if (block == 0 || block == 1 || block == 2){
        return 0;
    }
    if (block == 3 || block == 4 || block == 5 ) {
        return 3;
    }
    if (block == 6 || block == 7 || block <= 8 ) {
        return 6;
    }
    return 0;
}

bool checkRow(int ***arr, int block, int begin, int row, int value) {
    int count = 0;
    for (int block = begin; block < begin + 3; block++) {
        for (int col = 0; col < 3; col++) {
            if (*(*(*(arr + block) + row) + col) == value) {
                count++;
            }
        }
    }
    if (count == 1)
        return false;
    else
        return true;
}

int columnBegin(int block) {
    if (block == 0 || block == 3 || block == 6) {
        return 0;
    }
    else if (block == 1 || block == 4 || block == 7) {
        return 1;
    }
    else if (block == 2 || block == 5 || block == 8 ) {
        return 2;
    }
    return 0;
}

bool checkColumn(int ***arr, int block, int begin, int column, int value) {
	int count = 0;
    for (int block = begin; block < begin + 7; block+= 3) {
		for (int row = 0; row < 3; row++) {
			if (*(*(*(arr + block) + row) + column) == value) {
				count++;
			}
		}
	}
	if (count == 1)
		return false;
	else
		return true;
}

bool BlockCheck(int ***arr, int block, int value) {
	int count = 0;
	for (int row = 0; row < 3; row++) {
		for (int column = 0; column < 3; column++) {
			if (*(*(*(arr + block) + row) + column) == value) {
				count++;
			}
		}
	}
	if (count == 1)
		return false;
	else
		return true;
}

bool Place(int ***arr, int block, int BeginRow, int BeginColumn, int row, int column, int value) {
	if (checkRow(arr, block, BeginRow, row, value) && checkColumn(arr, block, BeginColumn, column, value) && BlockCheck(arr, block, value))
		return true;
	else
		return false;
}


/*
The main program reads a text file containing the block values of the Sudoku grid.
It then saves each 3x3 block into a 2D array. The Sudoku grid is composed of 9 3x3 blocks.
DO NOT MODIFY THE MAIN FUNTION!!!
*/
int main(int argc, char **argv) {
	if (argc != 2) {
		fprintf(stderr, "Usage: %s <file name>\n", argv[0]);
		return 2;
	}
    int i, j;
    FILE *fptr;
    int ***blocks = (int***)malloc(9 * sizeof(int**));

// Open file for reading
    fptr = fopen(argv[1], "r");
    if (fptr == NULL) {
        printf("Cannot Open File!\n");
        return 0;
    }

// Read 9x9 blocks into 2D arrays
    for(i=0; i<9; i++)
    {
        *(blocks+i) = (int**)malloc(3 * sizeof(int*));
        printf("Reading numbers in block %d... \n", i+1);
        for(j=0; j<3; j++)
        {
            *(*(blocks+i)+j) = (int*)malloc(3 * sizeof(int));

                fscanf(fptr, "%d %d %d", *(*(blocks+i)+j), *(*(blocks+i)+j)+1, *(*(blocks+i)+j)+2);
                printf("%d %d %d\n", *(*(*(blocks+i)+j)), *(*(*(blocks+i)+j)+1), *(*(*(blocks+i)+j)+2));
        }
    }

// Print out original Sudoku grid
    printf("Printing Sudoku before being solved:\n");
    printSudoku(blocks);

// Call solveSudoku and print out result
    printf("\nSolving Sudoku...\n\n");
    if(solveSudoku(blocks)){
        printf("Sudoku solved!\n");
        printSudoku(blocks);
    }
    else
        printf("This Sudoku cannot be solved!\n");

    return 0;
}

void printSudoku(int*** arr){
// Your implementation here
    
	int row = 0;
	while (row < 3) {
        for (int block = 0; block < 3; block++) {
			for (int column = 0; column < 3; column++) {
				printf("%d ", *(*(*(arr + block) + row) + column));
			}
			printf("|");
		}

		row++;
		printf("\n");
	}
	printf("---------------------\n");
    
	row = 0;
	while (row < 3) {

		for (int block = 3; block < 6; block++) {
			for (int column = 0; column < 3; column++) {
				printf("%d ", *(*(*(arr + block) + row) + column));
			}
			printf("|");
		}

		row++;
		printf("\n");
	}
	printf("---------------------\n");
    
	row = 0;
	while (row < 3) {
		for (int block = 6; block < 9; block++) {
			for (int column = 0; column < 3; column++) {
				printf("%d ", *(*(*(arr + block) + row) + column));
			}
			printf("|");
		}
		row++;
		printf("\n");
	}
}

int solveSudoku(int*** blocks){
// Your implementation here
    
	for (int box = 0; box < 9; box++) {
		for (int row = 0; row < 3; row++) {
			for (int column = 0; column < 3; column++) {

				if (isAvaliable(blocks, box, row, column)) {

					for (int value = 1; value <= 9; value++) {

						int BeginRow = rowBegin(box);
						int BeginColumn = columnBegin(box);
                        
						if (Place(blocks, box, BeginRow, BeginColumn, row, column, value)) {
							*(*(*(blocks + box) + row) + column) = value;

                            
							if (solveSudoku(blocks)) {
								return 1;
							}
							else {
								*(*(*(blocks + box) + row) + column) = 0;
							}
						}
					}
					return 0;
				}
			}
		}
	}
	return 1;
}

