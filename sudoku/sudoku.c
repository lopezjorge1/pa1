#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

bool correct(int ** matrix);
bool complete(int ** matrix);
bool search(int * a,int x);

struct element { //element of sudoku matrix
    int row;
    int column;
};

int main(int argc,char ** argv) {
    char * filename = NULL;
    FILE * f = NULL;
    int ** sudoku = NULL; //sudoku matrix
    char c; //represents each character in the file
    struct element  * first = NULL; //first zero in sudoku
    struct element  * second = NULL; //second zero in sudoku
    int count = 0; //number of zeros in the sudoku matrix

    if (argc != 2) {
        printf("error\n");
        exit(0);
    }

    filename = argv[1];

    //open the file to read
    f = fopen(filename,"r");

    //if there is no file
    if (f == NULL) {
        printf("error\n");
        exit(0);
    }

    //allocate space for sudoku matrix
    sudoku = (int **) malloc(9 * sizeof(int *));

    int i,j;
    for (i = 0; i < 9; i++) {
        sudoku[i] = (int *) malloc(9 * sizeof(int));
    }

    //input values into matrix
    for (i = 0; i < 9; i++) {
        for (j = 0; j < 9; j++) {
            fscanf(f,"%1c",&c);
            if (isdigit(c)) {
                sudoku[i][j] = c - '0'; //inserts the int value and not the ascii value
            } else {
                //set a variable that says there is a 0 in the matrix
                sudoku[i][j] = 0; //inserts a 0 element if a space char is encountered
                count++;
                if (count == 1) {
                    first = (struct element *) malloc(sizeof(struct element));
                    first->row = i;
                    first->column = j;
                } else {
                    second = (struct element *) malloc(sizeof(struct element));
                    second->row = i;
                    second->column = j;
                }
            }
        }
        fscanf(f,"\n");
    }

    if(!complete(sudoku)) {
        for (i = 1; i <= 9; i++) {
            for (j = 1; j <= 9; j++) {
                if (count == 2) sudoku[second->row][second->column] = j;
    
                sudoku[first->row][first->column] = i;
            
                if (correct(sudoku)) {
                    printf("solvable\n");
                    return 0;
                } 
            }
        }
        printf("unsolvable\n");
    } else {
        if (correct(sudoku)) {
            printf("correct\n");
        } else {
            printf("incorrect\n");
        }
    }
    
    fclose(f);
    free(sudoku);
    return 0;
}

bool correct(int ** matrix) {
    int unique[9] = {0}; //array that will maintain the numbers in each row, column,submatrix

    //loop through each row
    int i,j;
    for (i = 0; i < 9; i++) {
        for (j = 0; j < 9; j++) {
            int index = matrix[i][j] - 1; //the index of the value in unique array
    
            if (unique[index] != 0) {
                return false;
            }

            unique[index] = matrix[i][j];
        }
    
        memset(unique,0,9*sizeof(int)); //reset unique array for next row   
    }
    memset(unique,0,9*sizeof(int)); //reset unique array for columns
    //loop through each column
    for (i = 0; i < 9; i++) {
        for (j = 0; j < 9; j++) {
            int index = matrix[j][i] - 1;

            if (unique[index] != 0) {
                return false;
            }
            unique[index] = matrix[j][i];
        }
        memset(unique,0,9*sizeof(int));
    }
    memset(unique,0,9*sizeof(int)); //reset unique array for submatrices
    //loop through each 3x3 matrix
    int x = 0,y = 0; //indices to keep track of rows/columns of the submatrices
    for (i = 0; i < 9; i++) { //loop through 9 submatrices
        if (i % 3 == 0 && i > 0) {//for every 4th matrix increment the row index to +3 and reset the column index to 0
            x += 3;
            y = 0;
        }
    
        int tempx = x, tempy = y; //temp variables that holds the value of j and k 
        while (x < (tempx+3)) {
            while (y < (tempy+3)) {
                int index = matrix[x][y] - 1;
                
                if (unique[index] != 0) {
                    return false;
                }
                unique[index] = matrix[x][y];
                y++;
            }
            y = tempy; //reset k to whatever it was prior to iteration
            x++;
        }
        memset(unique,0,9*sizeof(int)); //reset the unique array to 0s
        y += 3; //increment the column index +3 after every submatrix
        x = tempx; //reset j to whatever is was prior to iteration
    }
    return true;
}

//perform a linear search and return true if element is found
bool search(int * a,int x) {
    int i;
    for (i = 0; i < 9; i++) {
        if (a[i] == x) {
            return true;
        }
    }
    return false;
}


bool complete(int ** matrix) {
    int i,j;
    for (i = 0; i < 9; i++) {
        for (j = 0; j < 9; j++) {
            if (matrix[i][j] == 0) {
                return false;
            }
        }
    }
    return true;
}

