//
// Created by Minseo Kim on 3/26/25.
//
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "matrix.h"
#include "fraction.h"
#include "../output/output.h"

/**
returns HEAP, matrix[] => if mxn matrix, it should go like:
if matrix is NULL it is initialized with zero-values
{a11,a12,...,a1n, a21,a22,... a2n,...,am1,...,amn}
returns NULL when malloc fails
**/
matrix_t* initialize_matrix(int row, int col, frac_t matrix[]) {
    matrix_t* mat;
    if(!(mat = (matrix_t *) malloc(sizeof (matrix_t)))) {
        perror("malloc failed");
        return NULL;
    }
    mat->col = col;
    mat->row = row;

    //allocate heap memory for each row and columns
    if(!(mat->matrix = (frac_t **) malloc(sizeof (frac_t *) * row))) {
        perror("malloc failed");
        free(mat);
        return NULL;
    }

    for(int i = 0; i< row; i++) {
        if(!(*(mat->matrix+i) = (frac_t *) malloc(sizeof (frac_t) * col))) {
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
                //init with 0/1
                (mat->matrix)[i][j].n = 0;
                (mat->matrix)[i][j].m = 1;
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
    frac_t ** matrix = mat->matrix;
    for(int i = 0; i < mat->row;i++) {
        free(matrix[i]);
    }
    free(matrix);
    free(mat);
}

void matrix_multiply(matrix_t* dest, matrix_t* A, matrix_t* B) {
    frac_t ** ab = dest->matrix;
    frac_t ** a = A->matrix;
    frac_t ** b = B->matrix;

    for(int i=0; i < dest->row;i++) {
        for(int j=0; j < dest->col;j++) {
            for(int k=0; k< A->col;k++) {
                frac_t a_ik = a[i][k];
                fr_multiply(&a_ik,b[k][j]); // a[i][k]*b[k][j]
                fr_add(&ab[i][j], a_ik);
            }
        }
    }
}


void print_matrix(matrix_t* mat) {
    frac_t ** matrix = mat->matrix;
    int maxstrlen = get_maxstrlen(mat);
    for(int i=0;i<mat->row;i++) {
        for(int j=0;j<mat->col;j++) {
            print_frac(matrix[i][j]);
            printAdditional_whitespaces(maxstrlen - frac_len(matrix[i][j]));
        }
        printf("\n");
    }
}