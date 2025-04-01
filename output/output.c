//
// Created by Minseo Kim on 3/30/25.
//
#include "output.h"
#include <stdio.h>

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

void print_divider(matrix_t* mat) {
    int maxstrlen = get_maxstrlen(mat);
    int length = (maxstrlen+1) * mat->col;
    for(int i=1;i<=length;i++) {
        printf("-");
    }
    printf("\n");
}