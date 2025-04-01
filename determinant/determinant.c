//
// Created by Minseo Kim on 3/31/25.
//

#include "determinant.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

/**
 * param:
 * matrix* m in gauss Form,
 * saved_mult: array of all saved multiplication constant during row normalization,
 * saved_multis: number of elements in saved_mult array
 * prints and returns the calculation and its result
 * **/
frac_t print_det_step(matrix_t* m,frac_t* saved_mult,int saved_multis) {
    frac_t result = {.n= (int) pow(-1,swap_num),.m=1};
    printf("Determinant = (-1)^(number of row swap operations) x all saved multiplying constant x product of all diagonal elements\n");
    printf("=\n( -1 )^%i",swap_num);

    //print all saved multiplying constants
    for(int i=0;i<saved_multis;i++) {
        printf("*( ");
        print_frac(saved_mult[i]);
        printf(")");
        fr_multiply(&result,saved_mult[i]);
    }

    //print diagonal elements
    printf("*( ");
    print_frac(m->matrix[0][0]);
    printf(")");
    for(int i=1;i<m->row;i++) {
        fr_multiply(&result,m->matrix[i][i]);
        printf("*( ");
        print_frac(m->matrix[i][i]);
        printf(")");
    }
    printf("= ");
    print_frac(result);
    printf("\n");
    return (frac_t) {.n=result.n,.m=result.m};
}

frac_t determinant(matrix_t* mat) {
    int piv[2] = {-1,-1};
    int curr_row = 0;
    int res = 0;
    int saveIndex = 0;
    frac_t * saved_mult = (frac_t*) calloc(mat->row,sizeof (frac_t));

    while((res=gauss_step(mat,piv,curr_row,NULL,NULL)) != END) {
        if(res == ROW_ADD) {
            curr_row++;
        }
        if(res == ROW_MULT) {
            printf("\nSAVE MULTIPLYING CONSTANT: ");
            print_frac(curr_mult);
            printf("\n");
            saved_mult[saveIndex++] = curr_mult;
        }
    }
    print_matrix(mat);
    frac_t det = print_det_step(mat,saved_mult,saveIndex);
    free(saved_mult);
    //reset global state variable
    mode_state = INITIAL;
    swap_num = 0;
    curr_mult = (frac_t) {.n=1,.m=1};
    return (frac_t) {.n=det.n,.m=det.m};
}
