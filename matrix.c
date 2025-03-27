//
// Created by Minseo Kim on 3/26/25.
//
#include <stdlib.h>
#include <stdio.h>
#include "matrix.h"

/**
returns HEAP, matrix[] => if mxn matrix, it should go like:
if matrix is NULL it is initialized with zero-values
{a11,a12,...,a1n, a21,a22,... a2n,...,am1,...,amn}
returns NULL when malloc fails
**/
matrix_t* initialize_matrix(int row, int col, int matrix[]) {
    matrix_t* mat;
    if(!(mat = (matrix_t *) malloc(sizeof (matrix_t)))) {
        perror("malloc failed");
        return NULL;
    }
    mat->col = col;
    mat->row = row;

    //allocate heap memory for each row and columns
    if(!(mat->matrix = (int**) malloc(sizeof (int*) * row))) {
        perror("malloc failed");
        free(mat);
        return NULL;
    }

    for(int i = 0; i< row; i++) {
        if(!(*(mat->matrix+i) = (int*) malloc(sizeof (int) * col))) {
            perror("malloc failed");
            for(int j=0;j<i;j++) {
                free(*(mat->matrix+j));
            }
            free(mat->matrix);
            free(mat);
            return NULL;
        }
    }
    //set data value(if matrix is NULL)
    if(!matrix) {
        for(int i = 0; i<row;i++) {
            for(int j = 0; j < col; j++) {
                (mat->matrix)[i][j] = 0;
            }
        }
        return mat;
    }
    //set data value
    for(int i = 0; i<row;i++) {
        for(int j = 0; j < col; j++) {
            (mat->matrix)[i][j] = matrix[j + i*col];
        }
    }

    return mat;
}

void free_matrix(matrix_t * mat) {
    int** matrix = mat->matrix;
    for(int i = 0; i < mat->row;i++) {
        free(matrix[i]);
    }
    free(matrix);
    free(mat);
}

void print_matrix(matrix_t* mat) {
    int ** matrix = mat->matrix;
    for(int i=0;i<mat->row;i++) {
        for(int j=0;j<mat->col;j++) {
            printf("%i ",matrix[i][j]);
        }
        printf("\n");
    }
}

void matrix_multiply(matrix_t* dest, matrix_t* A, matrix_t* B) {
    int** ab = dest->matrix;
    int** a = A->matrix;
    int** b = B->matrix;
    for(int i=0; i < dest->row;i++) {
        for(int j=0; j < dest->col;j++) {
            for(int k=0; k< A->col;k++) {
                ab[i][j] += (a[i][k]*b[k][j]);
            }
        }
    }
}