#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Argumentparser.c"
#include "gauss.h"
#include "determinant.h"

void mult_mode();
void inv_mode();
void gauss_mode();
void det_mode();

int main(int argc, char** argv) {

    printf("Welcome to Matrixop! Which Matrix operation do you want to see?\n");

    while(1) {
        printf("Press the number for the mode:\n");
        printf("1 Matrix multiplication\n2 Gauß-Algorithm\n3 Determinant\n4 Matrix Inversion\n");
        printf("press Q and Enter to end\n");
        char res[2];
        scanf("%1s",res);
        if(!strncmp(res,"Q",1)) {
            break;
        }
        else if (!strncmp(res,"1",1)) {
            mult_mode();
        }
        else if (!strncmp(res,"2",1)) {
            gauss_mode();
        }
        else if (!strncmp(res,"3",1)) {
            det_mode();
        }
        else if (!strncmp(res,"4",1)) {
            inv_mode();
        }
        else {
            printf("Wrong input, try again\n");
        }
    }
    printf("bye bye!\n");
    exit(EXIT_SUCCESS);
}

void mult_mode() {
    printf("input the matrices for AxB:\n\n");
    int row_a = 0;
    int row_b = 0;
    int col_a = 0;
    int col_b = 0;

    while(row_a <= 0) {
        printf("input must be greater than zero\n");
        printf("A row:");
        scanf("%i",&row_a);
    }
    while(col_a <= 0) {
        printf("input must be greater than zero\n");
        printf("A column:");
        scanf("%i",&col_a);
    }
    printf("matrix A:\n");
    getchar();
    frac_t * input_a = malloc(sizeof (frac_t)*row_a*col_a);

    while(1) {
        if(!read_matrix(input_a,row_a,col_a)) {
            break;
        }
    }
    matrix_t* A = initialize_matrix(row_a,col_a,input_a);
    free(input_a);


    while(row_b != col_a) {
        printf("row of B must be same as column of A\n");
        printf("B row:");
        scanf("%i",&row_b);

    }
    while(col_b <= 0) {
        printf("input must be greater than zero\n");
        printf("B column:");
        scanf("%i\n",&col_b);
    }

    frac_t * input_b = malloc(sizeof (frac_t) * row_b*col_b);
    while(1) {
        if(!read_matrix(input_b,row_b,col_b)) {
            break;
        }
    }
    matrix_t* B = initialize_matrix(row_b,col_b,input_b);
    free(input_b);
    printf("\n\n\n");
    matrix_t * res = initialize_matrix(row_a,col_b,NULL);
    print_matrix(A);
    printf("*\n");
    print_matrix(B);
    matrix_multiply(res,A,B);
    printf("=\n");
    print_matrix(res);

    free_matrix(res);
    free_matrix(A);
    free_matrix(B);
}

void gauss_mode() {
    printf("input matrix:\n");
    int row = 0;
    int col = 0;

    while(row <= 0) {
        printf("input must be greater than zero\n");
        printf("row:");
        scanf("%i",&row);
    }
    while(col <= 0) {
        printf("input must be greater than zero\n");
        printf("column:");
        scanf("%i",&col);
    }
    getchar();

    frac_t * inputarr = malloc(sizeof (frac_t)*row*col);

    while(1) {
        if(!read_matrix(inputarr,row,col)) {
            break;
        }
    }
    matrix_t* matrix = initialize_matrix(row,col,inputarr);
    printf("Gauß:\n");
    gauss(matrix);
    printf("reduced gauss (Reduced Row Echelon Form):\n");
    reduced_gauss(matrix);
    print_matrix(matrix);
    //reset global state variables
    mode_state = INITIAL;
    swap_num = 0;
    free_matrix(matrix);
}

void det_mode() {
    printf("input nxn matrix:\n");
    int n = 0;

    while(n <= 0) {
        printf("input must be greater than zero\n");
        printf("n:");
        scanf("%i",&n);
    }
    getchar();

    frac_t * inputarr = malloc(sizeof (frac_t)*n*n);

    while(1) {
        if(!read_matrix(inputarr,n,n)) {
            break;
        }
    }
    matrix_t* matrix = initialize_matrix(n,n,inputarr);
    determinant(matrix);
    free_matrix(matrix);
}

void inv_mode() {
    printf("Coming soon!\n");
}