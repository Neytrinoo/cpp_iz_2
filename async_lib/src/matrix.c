#include <stdio.h>
#include <malloc.h>

#include "matrix.h"

matrix_t *create_matrix(int rows, int cols) {
    matrix_t *matrix = calloc(1, sizeof(matrix_t));
    if (matrix == NULL) {
        return NULL;
    }

    matrix->arr = malloc(sizeof(double *) * rows + sizeof(double) * rows * cols);
    if (matrix->arr == NULL) {
        free(matrix);
        return NULL;
    }

    for (int i = 0; i < rows; ++i) {
        matrix->arr[i] = (double *) ((char *) matrix->arr + sizeof(double *) * rows + sizeof(double) * cols * i);
        for (int j = 0; j < cols; ++j) {
            matrix->arr[i][j] = 0;
        }
    }

    matrix->rows = rows;
    matrix->cols = cols;

    return matrix;
}

void print_matrix(FILE *file, matrix_t *matrix) {
    for (int i = 0; i < matrix->rows; ++i) {
        for (int j = 0; j < matrix->cols; ++j) {
            fprintf(file, "%lf ", matrix->arr[i][j]);
        }
        fprintf(file, "\n");
    }
}

void free_matrix(matrix_t *matrix) {
    free(matrix->arr);
    free(matrix);
}
