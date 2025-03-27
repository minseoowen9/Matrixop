//
// Created by Minseo Kim on 3/27/25.
//
#include "fraction.h"
#include <stdio.h>

//calculates gcd between a and b
int ggT(int a, int b) {
    int r1 = a < 0 ? -a: a;
    int r2 = b < 0 ? -b: b;
    while(r2) {
        int temp = r2;
        r2 = r1 % r2;
        r1 = temp;
    }
    return r1;
}

//intuition: dest += toAdd
void fr_add(frac_t * dest, frac_t * toAdd) {
    int new_n = dest->n * toAdd->m + toAdd->n * dest->m;
    int new_m = dest->m * dest-> m;
    int ggT = ggT(new_n,new_m);

    dest->n = new_n / ggT;
    dest->m = new_m / ggT;

}

void fr_multiply(frac_t* dest, frac_t* toMult) {
    int new_n = dest->n * toMult->n;
    int new_m = dest->m * dest-> m;
    int ggT = ggT(new_n,new_m);

    dest->n = new_n / ggT;
    dest->m = new_m / ggT;
}