#ifndef CPP_IZ_2_MATRIX_H
#define CPP_IZ_2_MATRIX_H

#include <stdio.h>

typedef struct {
    int rows;
    int cols;
    double **arr;
} matrix_t;

matrix_t *create_matrix(int rows, int cols);

void free_matrix(matrix_t *matrix);

void print_matrix(FILE *file, matrix_t *matrix);

#endif //CPP_IZ_2_MATRIX_H
