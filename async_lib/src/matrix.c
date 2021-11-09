#include <stdio.h>
#include <malloc.h>

#include "matrix.h"

matrix_t *create_matrix(int rows, int cols) {
    matrix_t *matrix = calloc(1, sizeof(matrix_t));
    if (matrix == NULL) {
        return NULL;
    }
    matrix->arr = calloc(rows * cols, sizeof(double));
    matrix->rows = rows;
    matrix->cols = cols;

    return matrix;
}

void print_matrix(FILE *file, matrix_t *matrix) {
    for (int i = 0; i < matrix->rows; ++i) {
        for (int j = 0; j < matrix->cols; ++j) {
            fprintf(file, "%lf ", matrix->arr[i * matrix->cols + j]);
        }
        fprintf(file, "\n");
    }
}

void free_matrix(matrix_t *matrix) {
    free(matrix->arr);
    free(matrix);
}
