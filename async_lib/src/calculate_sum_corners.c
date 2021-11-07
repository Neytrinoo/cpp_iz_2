#include <pthread.h>
#include <malloc.h>

#include "calculate_sum_corners.h"

#define COUNT_THREADS 10

double *calculate_sum_corners(matrix_t *matrix, int *length) {
    if (matrix == NULL || length == NULL || matrix->rows != matrix->cols) {
        return NULL;
    }

    pthread_t threads[COUNT_THREADS];
    data_t thread_contexts[COUNT_THREADS];

    *length = 2 * matrix->rows - 1;
    double *arr_of_sums = calloc(*length, sizeof(double));
    for (int i = 0; i < COUNT_THREADS; ++i) {
        thread_contexts[i].matrix = matrix;
        thread_contexts[i].corners_sum = arr_of_sums;
        thread_contexts[i].corner_start = i;
        thread_contexts[i].step = COUNT_THREADS;
        pthread_create(threads + i, NULL, sum_corners_thread, (void *) (thread_contexts + i));
    }

    for (int i = 0; i < COUNT_THREADS; ++i) {
        pthread_join(threads[i], NULL);
    }

    return arr_of_sums;
}

void sum_of_corner(matrix_t *matrix, int corner, double *res) {
    if (corner < matrix->rows) {
        for (int i = 0; i <= corner; ++i) {
            *res += matrix->arr[i][matrix->rows - 1 - corner + i];
        }
    } else {
        for (int i = 1 + corner % matrix->rows; i < matrix->rows; ++i) {
            *res += matrix->arr[i][matrix->rows - 1 - corner + i];
        }
    }
}

void *sum_corners_thread(void *data) {
    data_t *thread_context = data;
    for (int i = thread_context->corner_start; i < thread_context->matrix->rows * 2 - 1; i += thread_context->step) {
        sum_of_corner(thread_context->matrix, i, thread_context->corners_sum + i);
    }

    return NULL;
}
