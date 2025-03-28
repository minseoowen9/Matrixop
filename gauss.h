//
// Created by Minseo Kim on 3/28/25.
//

#ifndef MATRIXOP_GAUSS_H
#define MATRIXOP_GAUSS_H

#include "matrix.h"
#define SWAP 1
#define ROW_MULT 2
#define ROW_ADD 3
#define END 0

void swapRow(matrix_t* mat, int r1, int r2);
void rowAdd(matrix_t* mat, int dest_row,int mult_row, frac_t mult);
void row_product(matrix_t* mat, int row, frac_t mult);

//returns the first non-zero element row found, starting from row_start in col. Returns -1 if the column is zero-column
int find_NonZeroRow(matrix_t* mat, int col,int row_start);

/**
 * searches the next pivot element from current pivot
 * curr_piv[2]: {current pivot row, current pivot column}, if it is {-1,-1}, start from row 0, col 0 (initial)
 * set value: next found pivot row column in array. sets {-2,-2} if the pivot element is not found
 * **/
void find_nextpivot(matrix_t* mat, int curr_piv[2]);

/**
 * returns 0 if theres no more steps to compute, else macros defined above, which operation it has used
 * (for debug) logic: gauss_step is called when all of the element under curr_piv are zero and is about to operate the next step;
 * that is we are looking at a smaller matrix row:piv_row+1,...,row x col:piv_col+1,...,col
 **/
int gauss_step(matrix_t* mat, int curr_piv[],int current_row);
void gauss(matrix_t* mat);


#endif //MATRIXOP_GAUSS_H
