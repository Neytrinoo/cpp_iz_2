#include <gtest/gtest.h>
#include <iostream>
#include <chrono>

extern "C" {
#include <malloc.h>

#include "matrix.h"
#include "calculate_sum_corners.h"
}

void matrix_fill(matrix_t *matrix) {
    double elem = 1;
    for (int i = 0; i < matrix->rows; ++i) {
        for (int j = 0; j < matrix->cols; ++j) {
            matrix->arr[i * matrix->cols + j] = elem;
            elem += 1;
        }
    }
}


TEST(TimeTesting, test) {
    std::cout << "Time testing." << std::endl;
    int length;

    matrix_t *matrix1 = create_matrix(2000, 2000);
    matrix_fill(matrix1);

    auto begin_time1 = std::chrono::steady_clock::now();
    double *res_sum1 = calculate_sum_corners(matrix1, &length);
    auto end_time1 = std::chrono::steady_clock::now();
    auto elapsed_ms1 = std::chrono::duration_cast<std::chrono::milliseconds> (end_time1 - begin_time1);

    std::cout << "For matrix1 2000 x 2000: " << elapsed_ms1.count() << " ms" << std::endl;
    free_matrix(matrix1);
    free(res_sum1);

    matrix_t *matrix2 = create_matrix(10000, 10000);
    matrix_fill(matrix2);

    auto begin_time2 = std::chrono::steady_clock::now();
    double *res_sum2 = calculate_sum_corners(matrix2, &length);
    auto end_time2 = std::chrono::steady_clock::now();
    auto elapsed_ms2 = std::chrono::duration_cast<std::chrono::milliseconds> (end_time2 - begin_time2);

    std::cout << "For matrix1 10000 x 10000: " << elapsed_ms2.count() << " ms" << std::endl;
    free_matrix(matrix2);
    free(res_sum2);

    matrix_t *matrix3 = create_matrix(20000, 20000);
    matrix_fill(matrix3);

    auto begin_time3 = std::chrono::steady_clock::now();
    double *res_sum3 = calculate_sum_corners(matrix3, &length);
    auto end_time3 = std::chrono::steady_clock::now();
    auto elapsed_ms3 = std::chrono::duration_cast<std::chrono::milliseconds> (end_time3 - begin_time3);

    std::cout << "For matrix1 20000 x 20000: " << elapsed_ms3.count() << " ms" << std::endl;
    free_matrix(matrix3);
    free(res_sum3);
}

int main(int argc, char *argv[]) {
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}