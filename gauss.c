//
// Created by Minseo Kim on 3/28/25.
//
#include "gauss.h"
#include "output.h"
#include <stdio.h>
#include <stdlib.h>

#define INITIAL -1
#define END 0
#define SWAP 1
#define ROW_MULT 2
#define ROW_ADD 3

int mode_state = INITIAL;


void swapRow(matrix_t* mat, int r1, int r2) {
    frac_t ** m = mat->matrix;
    for(int i=0;i<mat->col;i++) {
        frac_t temp = m[r1][i];
        m[r1][i] = m[r2][i];
        m[r2][i] = temp;
    }
}

void rowAdd(matrix_t* mat, int dest_row,int mult_row, frac_t mult) { // dest_row + mult*multrow
    frac_t ** m = mat->matrix;
    for(int i=0;i<mat->col;i++) {
        frac_t mult_elem = m[mult_row][i];
        fr_multiply(&mult_elem,&mult);
        fr_add(&m[dest_row][i],&mult_elem);
    }
}

void row_product(matrix_t* mat, int row, frac_t mult) { // just row * mult(scalar)
    frac_t ** m = mat->matrix;
    for(int i=0;i<mat->col;i++) {
        fr_multiply(&m[row][i],&mult);
    }
}

//returns the first non-zero element row found, starting from row_start in col. Returns -1 if the column is zero-column
int find_NonZeroRow(matrix_t* mat, int col,int row_start) {
    for(int i=row_start;i<mat->row;i++) {
        if(mat->matrix[i][col].n != 0) {
            return i;
        }
    }
    return -1;
}

/**
 * searches the next pivot element from current pivot
 * curr_piv[2]: {current pivot row, current pivot column}, if it is {-1,-1}, start from row 0, col 0 (initial)
 * set value: next found pivot row column in array. sets {-2,-2} if the pivot element is not found
 * **/
void find_nextpivot(matrix_t* mat, int curr_piv[2]) {
    if(curr_piv[0] == mat->row-1 || curr_piv[1] == mat->col-1) {
        curr_piv[0] = -2;
        curr_piv[1] = -2;
        return;
    }

    for(int col= curr_piv[1]+1; col<mat->col;col++) {
        int res = find_NonZeroRow(mat,col,curr_piv[0]+1);
        if(res != -1) {
            curr_piv[0] = res;
            curr_piv[1] = col;
            return;
        }
    }
    curr_piv[0] = -2;
    curr_piv[1] = -2;
}

void print_gaussstep(matrix_t* mat,int rows_computed[],int mode,int const curr_piv[]) {
    frac_t ** m = mat->matrix;
    int maxstrlen = get_maxstrlen(mat);
    for(int i=0;i<mat->row;i++) {
        for(int j=0;j<mat->col;j++) {
            print_frac(m[i][j]);
            printAdditional_whitespaces(maxstrlen - frac_len(m[i][j]));
        }
        printf("| ");
        if(rows_computed[i]) {

            if(mode == SWAP) {
                printf("<- swap");
            }

            if(mode == ROW_MULT) {
                printf(" * ");
                frac_t pivot_val = m[curr_piv[0]][curr_piv[1]];
                frac_t mult = {.n= pivot_val.m, .m= pivot_val.n};
                print_frac(mult);
            }

            if(mode == ROW_ADD) {
                frac_t target = m[i][curr_piv[1]];
                frac_t minus = {.n=-1,.m=1};
                fr_multiply(&target,&minus);
                print_frac(target);
                printf("*row%i",curr_piv[0]);
            }
        }
        printf("\n");
    }
    print_divider(mat);
}

/**
 * returns 0(END) if theres no more steps to compute, else macros defined above, which operation it has used
 * (for debug) logic: gauss_step is called when all of the element under curr_piv are zero and is about to operate the next step;
 * that is we are looking at a smaller matrix row:piv_row+1,...,row x col:piv_col+1,...,col
 **/
int gauss_step(matrix_t* mat, int curr_piv[],int current_row) {
    if(mode_state == ROW_ADD || mode_state == INITIAL) {
        find_nextpivot(mat,curr_piv);
    }

    if(curr_piv[0] == -2) {
        return END;
    }
    int piv_row = curr_piv[0];
    int piv_col = curr_piv[1];
    frac_t ** m = mat->matrix;
    int* rows_computed = (int*) calloc(mat->row, sizeof (int));
    printf("pivot:\n");
    print_frac(m[curr_piv[0]][curr_piv[1]]);
    printf("\nat: row %i col %i\n",piv_row+1,piv_col+1);

    if(current_row != piv_row) { //swap (when our current row has zero value at non-zero column)
        mode_state = SWAP;
        printf("ROW SWAP\n");
        rows_computed[current_row] = 1;
        rows_computed[piv_row] = 1;
        print_gaussstep(mat,rows_computed,SWAP,curr_piv);
        free(rows_computed);

        swapRow(mat,current_row,piv_row);
        curr_piv[0] = current_row;
        return SWAP;
    } else if(m[piv_row][piv_col].n != m[piv_row][piv_col].m) { //pivot non 1=> make it 1
        mode_state = ROW_MULT;
        printf("ROW MULT\n");
        rows_computed[piv_row] = 1;
        print_gaussstep(mat,rows_computed,ROW_MULT,curr_piv);
        free(rows_computed);

        row_product(mat,piv_row,(frac_t) {.n= m[piv_row][piv_col].m, .m= m[piv_row][piv_col].n});
        return ROW_MULT;
    } else { //row addition
        mode_state = ROW_ADD;
        printf("ROW ADDITION\n");

        //initialize rows_computed and print the matrix first before it is changed by rowAdd operation
        for(int i=piv_row+1;i<mat->row;i++) {
            if(m[i][piv_col].n == 0) {
                continue;
            }
            rows_computed[i] = 1;
        }
        print_gaussstep(mat,rows_computed,ROW_ADD,curr_piv);
        free(rows_computed);

        //compute rowAdd
        for(int i=piv_row+1;i<mat->row;i++) {
            if(m[i][piv_col].n == 0) {
                continue;
            }
            frac_t mult_const = m[i][piv_col];
            frac_t minus = {.n= -1, .m= 1};
            fr_multiply(&mult_const,&minus);

            rowAdd(mat,i,piv_row,mult_const);
        }

        return ROW_ADD;
    }
}

void gauss(matrix_t* mat) {
    int piv[2] = {-1,-1};
    int curr_row = 0;
    int res = 0;
    while((res=gauss_step(mat,piv,curr_row)) != END) {
        if(res == ROW_ADD) {
            curr_row++;
        }
    }
    print_matrix(mat);
}