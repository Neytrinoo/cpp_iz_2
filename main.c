#include <stdio.h>
#include <sys/time.h>
#include <inttypes.h>

#include "matrix.h"
#include "calculate_sum_corners.h"

int main() {
    matrix_t *matrix = create_matrix(10000, 10000);
    int count = 1;
    for (int i = 0; i < matrix->rows; ++i) {
        for (int j = 0; j < matrix->cols; ++j) {
            matrix->arr[i][j] = count++;
        }
    }

    int length;
    struct timeval tv_start, tv_end;
    gettimeofday(&tv_start, NULL);
    double *res = calculate_sum_corners(matrix, &length);
    gettimeofday(&tv_end, NULL);
    int64_t res_time = (tv_end.tv_sec - tv_start.tv_sec) * 1000000LL + (tv_end.tv_usec - tv_start.tv_usec);
    printf("%ld\n", res_time);
    printf("%lf", *res);


    return 0;
}
