#include <gtest/gtest.h>
#include <iostream>
#include <chrono>

extern "C" {
#include <malloc.h>

#include "matrix.h"
#include "calculate_sum_corners.h"
}

void matrix_fill(matrix_t *matrix, std::initializer_list<double> values) {
    auto now_values = values.begin();
    for (int i = 0; i < matrix->rows; ++i) {
        for (int j = 0; j < matrix->cols; ++j) {
            matrix->arr[i * matrix->cols + j] = *now_values;
            now_values++;
        }
    }
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

class MatrixFromTwoToFiveElemTest : public ::testing::Test {
protected:
    void SetUp() {
        matrix2 = create_matrix(2, 2);
        matrix_fill(matrix2);

        matrix3 = create_matrix(3, 3);
        matrix_fill(matrix3);

        matrix4 = create_matrix(4, 4);
        matrix_fill(matrix4);

        matrix5 = create_matrix(5, 5);
        matrix_fill(matrix5);
    }

    void TearDown() {
        free_matrix(matrix2);
        free_matrix(matrix3);
        free_matrix(matrix4);
        free_matrix(matrix5);
    }

    matrix_t *matrix2;
    matrix_t *matrix3;
    matrix_t *matrix4;
    matrix_t *matrix5;
};

TEST(MatrixOneElemTest, test) {
    matrix_t *matrix = create_matrix(1, 1);
    matrix_fill(matrix, {1});

    int length;

    double *res_sum = calculate_sum_corners(matrix, &length);
    EXPECT_EQ(length, 1);
    EXPECT_DOUBLE_EQ(*res_sum, 1.0);

    free_matrix(matrix);
    free(res_sum);
}

TEST_F(MatrixFromTwoToFiveElemTest, test) {
    int length;

    double *res_sum2 = calculate_sum_corners(matrix2, &length);
    double expected_result2[] = {2, 5, 3};
    EXPECT_EQ(length, 3);
    for (int i = 0; i < length; ++i) {
        EXPECT_DOUBLE_EQ(res_sum2[i], expected_result2[i]);
    }
    free(res_sum2);

    double *res_sum3 = calculate_sum_corners(matrix3, &length);
    double expected_result3[] = {3, 8, 15, 12, 7};
    EXPECT_EQ(length, 5);
    for (int i = 0; i < length; ++i) {
        EXPECT_DOUBLE_EQ(res_sum3[i], expected_result3[i]);
    }
    free(res_sum3);

    double *res_sum4 = calculate_sum_corners(matrix4, &length);
    double expected_result4[] = {4, 11, 21, 34, 30, 23, 13};
    EXPECT_EQ(length, 7);
    for (int i = 0; i < length; ++i) {
        EXPECT_DOUBLE_EQ(res_sum4[i], expected_result4[i]);
    }
    free(res_sum4);

    double *res_sum5 = calculate_sum_corners(matrix5, &length);
    double expected_result5[] = {5, 14, 27, 44, 65, 60, 51, 38, 21};
    EXPECT_EQ(length, 9);
    for (int i = 0; i < length; ++i) {
        EXPECT_DOUBLE_EQ(res_sum5[i], expected_result5[i]);
    }
    free(res_sum5);
}

TEST(MatrixWithZeroTest, test) {
    matrix_t *matrix = create_matrix(4, 4);
    matrix_fill(matrix, {1, 1, 0, 0, 0, 0, 1, 1, -1, -1, 0, 1, 0, 0, 0, 0});
    int length;
    double *res_sum = calculate_sum_corners(matrix, &length);
    double expected_result[] = {0, 1, 3, 1, -1, -1, 0};
    EXPECT_EQ(length, 7);
    for (int i = 0; i < length; ++i) {
        EXPECT_DOUBLE_EQ(res_sum[i], expected_result[i]);
    }

    free_matrix(matrix);
    free(res_sum);
}

TEST(NullValueTest, test) {
    int length;
    double *res_sum = calculate_sum_corners(nullptr, &length);
    EXPECT_EQ(res_sum, nullptr);
    free(res_sum);

    matrix_t *matrix = create_matrix(2, 2);
    res_sum = calculate_sum_corners(matrix, nullptr);
    EXPECT_EQ(res_sum, nullptr);
    free(res_sum);
    free_matrix(matrix);

    res_sum = calculate_sum_corners(nullptr, nullptr);
    EXPECT_EQ(res_sum, nullptr);
    free(res_sum);
}


int main(int argc, char *argv[]) {
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}