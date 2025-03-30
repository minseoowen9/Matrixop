//
// Created by Minseo Kim on 3/27/25.
//

#ifndef MATRIXOP_MATRIX_H
#define MATRIXOP_MATRIX_H

#include "fraction.h"

typedef struct Matrix {
    int row;
    int col;
    frac_t ** matrix;
} matrix_t;

matrix_t* initialize_matrix(int row, int col, frac_t matrix[]);
void free_matrix(matrix_t * mat);
void print_matrix(matrix_t* mat);
void matrix_multiply(matrix_t* dest, matrix_t* A, matrix_t* B);
int get_maxstrlen(matrix_t* mat);
void printAdditional_whitespaces(int x);

#endif //MATRIXOP_MATRIX_H
