#include <malloc.h>

#include "calculate_sum_corners.h"

double *calculate_sum_corners(matrix_t *matrix, int *length) {
    if (matrix == NULL || length == NULL || matrix->rows != matrix->cols) {
        return NULL;
    }

    *length = 2 * matrix->rows - 1;
    double *arr_of_sums = calloc(*length, sizeof(double));

    for (int i = 0; i < matrix->rows; ++i) {
        for (int j = 0; j < matrix->cols; ++j) {
            arr_of_sums[matrix->rows - 1 - j + i] += matrix->arr[i * matrix->cols + j];
        }
    }

    return arr_of_sums;
}
