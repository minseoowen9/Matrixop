//
// Created by Minseo Kim on 3/27/25.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fraction.h"
#include <regex.h>

int isNumber(char* str) {
    regex_t reg;
    if(regcomp(&reg,"^[0-9]+$",REG_EXTENDED)) {
        printf("regex init fail");
        exit(EXIT_FAILURE);
    }
    if(regexec(&reg,str,0,NULL,0)) {
        return 0;
    }
    regfree(&reg);
    return 1;
}

int isFraction(char* str) {
    regex_t reg;
    if(regcomp(&reg,"^[0-9]+/[1-9][0-9]*$",REG_EXTENDED)) {
        printf("regex init fail");
        exit(EXIT_FAILURE);
    }
    if(regexec(&reg,str,0,NULL,0)) {
        return 0;
    }
    regfree(&reg);
    return 1;
}

int parseFraction(frac_t* dest, char* tok) {
    if(isNumber(tok)) {
        int nom = atol(tok);
        int dom = 1;
        dest->n = nom;
        dest->m = dom;
        return 0;
    }
    if(isFraction(tok)) {
        char* saveptr;
        char* nom = strtok_r(tok, "/",&saveptr);
        char* dom = strtok_r(NULL, "/",&saveptr);

        if(!nom || !dom) return 1;

        dest->n = atol(nom);
        dest->m = atol(dom);
        return 0;
    }
    return 1;
}

int read_matrix(frac_t* matrix, int row, int col) {
    char buf[256];
    int index = 0;

    for (int i = 0; i < row; i++) {
        fgets(buf, sizeof buf, stdin); // Read a full line
        char *token = strtok(buf, " \n");
        int read_col = 0;

        while (token) {
            read_col++;
            if(parseFraction(&matrix[index],token)) {
                printf("not in number or in fraction. Check if denominator is non-zero\n");
                return 1;
            }
            index++;
            token = strtok(NULL, " \n"); // Get next token
        }
        if(read_col != col) {
            printf("column number unmatch\n");
            return 1;
        }
    }
    return 0;
}