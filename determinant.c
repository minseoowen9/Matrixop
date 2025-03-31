//
// Created by Minseo Kim on 3/31/25.
//

#include "determinant.h"
#include <stdio.h>
#include <math.h>

/**
 * param: matrix* m in gauss Form
 * prints the calculation and its result
 * **/
void print_det_steps(matrix_t* m) {
    frac_t result = {.n= (int) pow(-1,swap_num),.m=1};
    printf("Determinant = (-1)^(number of row swap operations) x product of all diagonal elements\n");
    printf("=> (-1)^(number of row swap operations)*m[1][1]");
    for(int i=1;i<m->row;i++) {
        printf("*m[%i][%i]",i+1,i+1);
    }
    printf("=\n(%i)*",result.n);
    print_frac(m->matrix[0][0]);

    for(int i=1;i<m->row;i++) {
        frac_t mult = m->matrix[i][i];
        fr_multiply(&result,&mult);
        printf("*( ");
        print_frac(m->matrix[i][i]);
        printf(")");
    }
    printf("=\n");
    print_frac(result);
    printf("\n");
}

void determinant(matrix_t* mat) {
    gauss(mat);
    print_matrix(mat);
    print_det_steps(mat);
    //reset global state variable
    mode_state = INITIAL;
    swap_num = 0;
}
