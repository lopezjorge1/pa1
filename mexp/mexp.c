#include <stdlib.h>
#include <stdio.h>

int ** exponentiate(int ** base,int size,int exponent);
int ** multiply(int ** m,int ** base,int size);

int main(int argc,char ** argv) {
    char * filename = NULL;
    FILE * f = NULL;
    int size;
    int ** base; //base matrix
    int ** result; //result matrix
    int exponent; //exponent base matrix will be raised to

    if (argc != 2) {
        printf("error\n");
        exit(0);
    }

    filename = argv[1];

    f = fopen(filename,"r");

    if (f == NULL) {
        printf("error\n");
        exit(0);
    }

    fscanf(f,"%d\n",&size);

    //allocate memory for every column in the matrix
    base = (int **) malloc(size * sizeof(int *));

    //allocate memory for the rows of the matrix
    int i;
    for (i = 0; i < size; i++) {
        base[i] = (int *) malloc(size * sizeof(int));
    }
    int x,y;
    //input matrix values
    for (x = 0; x < size; x++) {
        for (y = 0; y < size; y++) {
            fscanf(f,"%d\t ",&base[x][y]);
        }
        fscanf(f,"\n");
    }

    //get the exponent value
    fscanf(f,"%d\n",&exponent);

    result = exponentiate(base,size,exponent); 
    
    //print result matrix
    for (x = 0; x < size; x++) {
        for (int y = 0; y < size-1; y++) {
            printf("%d ",result[x][y]);
        }
        printf("%d",result[x][size-1]);
        printf("\n");
    }

    //free memory in the matrices
    for (i = 0; i < size; i++) {
        free(base[i]);
        free(result[i]);
    }

    free(base);
    free(result);
    fclose(f);
    return 0;
}

int ** exponentiate(int ** base,int size,int exponent) {
    int ** product = NULL; //product
    int ** m = base; //product after multiplying n times

    //if exponent of 1 return base
    if (exponent == 1) {
        return base;
    }

    int i;
    for (i = 0; i < exponent-1; i++) {
        product = multiply(m,base,size);
        m = product;
    }

    return product;
}

int ** multiply(int ** m,int ** base,int size) {
    //allocate space for result matrix
    int ** result = (int **) malloc(size * sizeof(int *));

    int i,j,k;
    for (i = 0; i < size; i++) {
        result[i] = (int *) malloc(size * sizeof(int));
        //set every element in the matrix to 0
        for (j = 0; j < size; j++) {
            result[i][j] = 0;
        }
    }

    //multiply the m matrix by the base matrix
    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++) {
            for (k = 0; k < size; k++) {
                result[i][j] += m[i][k] * base[k][j];
            }
        }
    }

    return result;
}
