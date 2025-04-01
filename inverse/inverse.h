//
// Created by Minseo Kim on 4/1/25.
//

#ifndef MATRIXOP_INVERSE_H
#define MATRIXOP_INVERSE_H

#include "../gauss/gauss.h"

void print_inverse_callback(matrix_t* toInverse,int currentRow);
matrix_t* initialize_I_matrix(int n);

#endif //MATRIXOP_INVERSE_H
