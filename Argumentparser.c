//
// Created by Minseo Kim on 3/27/25.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int read_matrix(int* matrix, int row, int col) {
    char buf[256];
    int index = 0;

    for (int i = 0; i < row; i++) {
        fgets(buf, sizeof buf, stdin); // Read a full line
        char *token = strtok(buf, " \n");
        int read_col = 0;

        while (token) {
            read_col++;
            matrix[index++] = atoi(token); // Convert to int and store
            token = strtok(NULL, " \n"); // Get next token
        }
        if(read_col != col) {
            printf("column number unmatch\n");
            return 1;
        }
    }
    return 0;
}