#include <stdio.h>

#define COLUMNS 3 // no of columns of the matrix
#define ROWS 3 // no of rows of the matrix

void print_matrix(double *row_ptrs[]);
void swap_rows(double *row_ptrs[], int row_a_index, int row_b_index);
void subtract_rows(double *row_ptrs[], int row_a_index, int row_b_index, double multiplier, int start_column);

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

    // start elimination

    int i, j, k;
    double pivot, multiplier;
    double *pivot_row_ptr, *eliminate_row_ptr;

    for(k = 0; k < ROWS - 1; k++){
        pivot_row_ptr = row_ptrs[k];
        pivot = *(pivot_row_ptr + k);
        for(i = k + 1; i < ROWS; i++){
            eliminate_row_ptr = row_ptrs[i];
            multiplier = *(eliminate_row_ptr + k) / pivot;
            subtract_rows(row_ptrs, i, k, multiplier, k);
        }
    }

    printf("The eliminated matrix is:\n");
    print_matrix(row_ptrs);

    return 0;

}

void print_matrix(double *row_ptrs[]){

    int i, j;

    double *temp_ptr; // temporary pointer to a row

    for(i = 0; i < ROWS; i++, row_ptrs++){
        temp_ptr = *row_ptrs;
        for(j = 0; j < COLUMNS; j++, temp_ptr++){
            printf("%f ", *temp_ptr);
        }
        printf("\n");
    }

}

void swap_rows(double *row_ptrs[], int row_a_index, int row_b_index){

    double *temp_ptr;

    temp_ptr = *(row_ptrs + row_a_index);
    *(row_ptrs + row_a_index) = *(row_ptrs + row_b_index);
    *(row_ptrs + row_b_index) = temp_ptr;

}

// subtracts multiplier * row_b from row_a starting at the column number start_column
void subtract_rows(double *row_ptrs[], int row_a_index, int row_b_index, double multiplier, int start_column){

    int i;
    double *temp_row_a_ptr, *temp_row_b_ptr;
    temp_row_a_ptr = *(row_ptrs + row_a_index) + start_column;
    temp_row_b_ptr = *(row_ptrs + row_b_index) + start_column;

    for(i = 0; i < COLUMNS; i++, temp_row_a_ptr++, temp_row_b_ptr++){
        *temp_row_a_ptr -= multiplier * *temp_row_b_ptr;
    }

}
