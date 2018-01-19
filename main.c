#include <stdio.h>
#include <math.h>

#define COLUMNS 3 // no of columns of the matrix
#define ROWS 2 // no of rows of the matrix

void print_matrix(double *row_ptrs[]);
void swap_rows(double *row_ptrs[], int row_a_index, int row_b_index);
void subtract_rows(double *row_ptrs[], int row_a_index, int row_b_index, double multiplier, int start_column);
int perform_partial_pivoting(double *row_ptrs[], double abs_pivot_value, int pivot_row_index, int pivot_column_index);

main(){

    // work with a hard coded matrix for now
    double matrix_values[COLUMNS * ROWS] = {
        0.00300, 59.14, 59.17, 5.291, -6.130, 46.78
    };
    // array of pointers that point to the start of a matrix row
    double *row_ptrs[ROWS]; 
    
    row_ptrs[0] = &matrix_values[0];
    row_ptrs[1] = &matrix_values[3];

    // start elimination

    int i, j, k;
    double pivot, multiplier;
    double *pivot_row_ptr, *eliminate_row_ptr;

    for(k = 0; k < ROWS - 1; k++){
        if( fabs(*(row_ptrs[k] + k)) < 1 ){
            // perform partial pivoting
            int row_index_of_largest_pivot;
            row_index_of_largest_pivot = perform_partial_pivoting(row_ptrs, fabs(*(row_ptrs[k] + k)), k, k);
            if(row_index_of_largest_pivot > 0){
                // a row with a larger absolute value pivot was found, so swap them
                swap_rows(row_ptrs, k, row_index_of_largest_pivot);
            }
        }
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

// returns the index of the row with the pivot with the largest absolute value
int perform_partial_pivoting(double *row_ptrs[], double abs_pivot_value, int pivot_row_index, int pivot_column_index){

    int i; // loop variable
    int row_index_of_largest_pivot = -1; // row index with largest pivot absolute value
    double *temp_row_ptr;

    // offset row_ptrs to start at the row below the original pivot row
    row_ptrs += pivot_row_index + 1;

    for(i = pivot_row_index + 1; i < ROWS; i++, row_ptrs++){
        temp_row_ptr = *row_ptrs;
        if( fabs(*(temp_row_ptr + pivot_column_index)) > abs_pivot_value ){
            abs_pivot_value = fabs(*(temp_row_ptr + pivot_column_index));
            row_index_of_largest_pivot = i;
        }
    }

    return row_index_of_largest_pivot;

}
