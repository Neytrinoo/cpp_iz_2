#ifndef CPP_IZ_2_CALCULATE_SUM_CORNERS_H
#define CPP_IZ_2_CALCULATE_SUM_CORNERS_H

#include "matrix.h"

typedef struct {
    matrix_t *matrix;
    int corner_start;
    int step;
    double *corners_sum;
} data_t;

/**
 * Вычисляет суммы элементов квадратной матрицы (суммы элементов, расположенных на диагонали и параллельной ей отрезках)
 * и возвращает указатель на область памяти, в которую запишутся результаты (самый первый элемент - сумма элементов
 * правого верхнего отрезка, самый последний - левого нижнего)
 * @param matrix указатель на матрицу
 * @param length сюда будет записана длина итогового массива (хоть она и всегда заранее известна)
 * @return массив сумм или NULL, если произошла ошибка (передан нулевой указатель, либо матрица не квадратрная)
 */
double *calculate_sum_corners(matrix_t *matrix, int *length);


/**
 * Вычисляет сумму элементов на угле матрицы
 * @param matrix указатель на матрицу
 * @param corner номер угла
 * @return сумма элементов угла
 */
void sum_of_corner(matrix_t *matrix, int corner, double *res);

/**
 * Суммирует все углы, начинающиеся с corner_start с шагом step. Результат записывается в массив corners_sum
 * @param matrix указатель на матрицу
 * @param corner_start стартовый угол
 * @param step шаг
 */
void *sum_corners_thread(void *data_t);

#endif //CPP_IZ_2_CALCULATE_SUM_CORNERS_H
