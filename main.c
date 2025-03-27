#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Argumentparser.c"
#include "matrix.h"

void mult_mode();
void inv_mode();
void gauss_mode();

int main(int argc, char** argv) {
    printf("Welcome to Matrixop! Which Matrix operation do you want to see?\n");

    while(1) {
        printf("Press the number for the mode:\n");
        printf("1 Matrix multiplication \n2 Matrix Inversion\n3 Gauß-Algorithm\n");
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
            inv_mode();
        }
        else if (!strncmp(res,"3",1)) {
            gauss_mode();
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
    int* matrix_a = malloc(sizeof (int)*row_a*col_a);

    while(1) {
        if(!read_matrix(matrix_a,row_a,col_a)) {
            break;
        }
    }
    matrix_t* A = initialize_matrix(row_a,col_a,matrix_a);
    free(matrix_a);


    while(row_b != col_a) {
        printf("row of B must be same as column of A\n");
        printf("B row:");
        scanf("%i",&row_b);

    }
    while(col_b <= 0) {
        printf("input must be greater than zero\n");
        printf("B column:");
        scanf("%i",&col_b);
    }

    int* matrix_b = malloc(sizeof (int) * row_b);
    while(1) {
        if(!read_matrix(matrix_b,row_b,col_b)) {
            break;
        }
    }
    matrix_t* B = initialize_matrix(row_b,col_b,matrix_b);
    free(matrix_b);

    matrix_t * res = initialize_matrix(row_a,col_b,NULL);
    matrix_multiply(res,A,B);
    printf("result:\n");
    print_matrix(res);

    free_matrix(res);
    free_matrix(A);
    free_matrix(B);
}

void inv_mode() {

}

void gauss_mode() {

}