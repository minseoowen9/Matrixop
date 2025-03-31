//
// Created by Minseo Kim on 3/27/25.
//

#ifndef MATRIXOP_FRACTION_H
#define MATRIXOP_FRACTION_H

//represents n/m
typedef struct Fraction {
    int n;
    int m;
} frac_t;

void fr_add(frac_t* dest, frac_t toAdd);
void fr_multiply(frac_t* dest, frac_t toMult);
int frac_len(frac_t fr);
void print_frac(frac_t fr);


#endif //MATRIXOP_FRACTION_H
