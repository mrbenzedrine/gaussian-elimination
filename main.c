#include <stdio.h>

#define COLUMNS 3 // no of columns of the matrix
#define ROWS 3 // no of rows of the matrix

void print_matrix(double *row_ptrs[]);

main(){

    // work with a hard coded matrix for now
    double matrix_values[COLUMNS * ROWS] = {
        1,2,4,3,8,14,2,6,13
    };
    // array of pointers that point to the start of a matrix row
    double *row_ptrs[ROWS]; 
    
    row_ptrs[0] = &matrix_values[0];
    row_ptrs[1] = &matrix_values[3];
    row_ptrs[2] = &matrix_values[6];

    return 0;

}

void print_matrix(double *row_ptrs[]){

    int i, j;

    for(i = 0; i < ROWS; i++, row_ptrs++){
        for(j = 0; j < COLUMNS; j++, (*row_ptrs)++){
            printf("%f ", **row_ptrs);
        }
        printf("\n");
    }

}
