//
// Created by Minseo Kim on 3/26/25.
//
#include <stdlib.h>
#include <stdio.h>
#include "matrix.h"
#include "fraction.h"
#include <string.h>

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
                frac_t b_kj = b[k][j];
                fr_multiply(&a_ik,&b_kj); // a[i][k]*b[k][j]
                fr_add(&ab[i][j], &a_ik);
            }
        }
    }
}

int frac_len(frac_t fr) {
    char n[12];
    char m[12];
    sprintf(n,"%d",fr.n);
    sprintf(m,"%d",fr.m);
    if(fr.n == 0) { // 0/n => 0
        return 1;
    } else if(fr.m == 1) { // 100/1 => 100
        return strlen(n);
    }
    return strlen(n) + strlen(m) + 1; // the fraction is represented in a/b, adding length for '/'
}

int get_maxstrlen(matrix_t* mat) {
    frac_t ** matr = mat->matrix;
    int maxlen = 0;
    for(int i=0;i<mat->row;i++) {
        for(int j=0;j<mat->col;j++) {
            int strlength = frac_len(matr[i][j]);
            if(maxlen < strlength) {
                maxlen = strlength;
            }
        }
    }
    return maxlen;
}

void printAdditional_whitespaces(int x) {
    for(int i=0;i<x;i++) {
        printf(" ");
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