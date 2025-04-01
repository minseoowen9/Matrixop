//
// Created by Minseo Kim on 4/1/25.
//

#ifndef MATRIXOP_ARGUMENTPARSER_H
#define MATRIXOP_ARGUMENTPARSER_H

#include "../types/fraction.h"

int isNumber(char* str);
int isFraction(char* str);
int parseFraction(frac_t* dest, char* tok);
int read_matrix(frac_t* matrix, int row, int col);

#endif //MATRIXOP_ARGUMENTPARSER_H
