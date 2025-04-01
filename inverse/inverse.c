//
// Created by Minseo Kim on 4/1/25.
//

#include "inverse.h"
#include <stdlib.h>
#include <stdio.h>
#include "../output/output.h"

void print_inverse_callback(matrix_t* toInverse,int currentRow) {

    frac_t ** m = toInverse->matrix;
    int maxstrlen = get_maxstrlen(toInverse);
    for(int j=0;j<toInverse->col;j++) {
        print_frac(m[currentRow][j]);
        printAdditional_whitespaces(maxstrlen - frac_len(m[currentRow][j]));
    }
    printf("| ");
}

void normalize_fracarr(int n,frac_t * fracarr) {
    for(int i=0;i<n*n;i++) {
        fracarr[i].m = 1;
    }
}

matrix_t* initialize_I_matrix(int n) {
    frac_t* num_arr = calloc(n*n,sizeof (frac_t));
    normalize_fracarr(n,num_arr); // So that 0/0 is avoided
    int dist = 0;
    for(int i=0;i<n*n;i+=n) {
        num_arr[i+dist++] = (frac_t) {.n=1,.m=1};
    }
    matrix_t * res = initialize_matrix(n,n,num_arr);
    free(num_arr);
    return res;
}