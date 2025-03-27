//
// Created by Minseo Kim on 3/27/25.
//

#ifndef MATRIXOP_MATRIX_H
#define MATRIXOP_MATRIX_H

typedef struct Matrix {
    int row;
    int col;
    int ** matrix;
} matrix_t;

matrix_t* initialize_matrix(int row, int col, int matrix[]);
void free_matrix(matrix_t * mat);
void print_matrix(matrix_t* mat);
void matrix_multiply(matrix_t* dest, matrix_t* A, matrix_t* B);

#endif //MATRIXOP_MATRIX_H
