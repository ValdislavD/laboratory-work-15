#include "libs/data_structures/matrix/matrix.h"
#include <stdlib.h>
#include <string.h>
#include <windows.h>

void swapRowsWithMinAndMax(matrix *m) {
    // Находим позиции минимального и максимального элементов
    position minPos = getMinValuePos(*m);
    position maxPos = getMaxValuePos(*m);

    // Поменять местами строки с минимальным и максимальным элементами
    swapRows(m, minPos.rowIndex, maxPos.rowIndex);
}

int getMax(int *a, int n) {
    int max = a[0];
    for (int i = 1; i < n; i++) {
        if (a[i] > max) {
            max = a[i];
        }
    }
    return max;
}

void sortRowsByMaxElement(matrix *m) {
    int nRows = m->nRows;
    // Создаем временный массив для хранения максимальных элементов строк и их индексов
    int *maxValues = (int *)malloc(nRows * sizeof(int));
    int *indices = (int *)malloc(nRows * sizeof(int));

    // Заполняем массивы максимальными значениями и индексами строк
    for (int i = 0; i < nRows; i++) {
        maxValues[i] = getMax(m->values[i], m->nCols);
        indices[i] = i;
    }

    // Сортируем массив индексов строк по соответствующим максимальным значениям
    for (int i = 1; i < nRows; i++) {
        int key = maxValues[i];
        int index = indices[i];
        int j = i - 1;

        while (j >= 0 && maxValues[j] > key) {
            maxValues[j + 1] = maxValues[j];
            indices[j + 1] = indices[j];
            j = j - 1;
        }
        maxValues[j + 1] = key;
        indices[j + 1] = index;
    }

    // Создаем временную матрицу для хранения отсортированных строк
    matrix sorted = getMemMatrix(m->nRows, m->nCols);

    // Копируем строки в порядке, определенном отсортированным массивом индексов
    for (int i = 0; i < nRows; i++) {
        memcpy(sorted.values[i], m->values[indices[i]], m->nCols * sizeof(int));
    }

    // Освобождаем память от временных массивов
    free(maxValues);
    free(indices);

    // Заменяем исходную матрицу на отсортированную
    freeMemMatrix(m);
    *m = sorted;
}

int main() {
    SetConsoleOutputCP(CP_UTF8);
    // Создаем и заполняем квадратную матрицу
    matrix squareMatrix = createMatrixFromArray((const int[]){5, 8, 3, 2}, 2, 2);
    outputMatrix(squareMatrix);

    // Задача 1: Поменять местами строки с минимальным и максимальным элементами
    swapRowsWithMinAndMax(&squareMatrix);
    outputMatrix(squareMatrix);

    // Создаем и заполняем матрицу для задачи 2
    matrix matrixForSorting = createMatrixFromArray((const int[]){7, 1, 2, 1, 8, 1, 3, 2, 3}, 3, 3);
    outputMatrix(matrixForSorting);

    // Задача 2: Сортировка строк по неубыванию наибольших элементов
    sortRowsByMaxElement(&matrixForSorting);
    outputMatrix(matrixForSorting);

    // Освобождаем память от матриц
    freeMemMatrix(&squareMatrix);
    freeMemMatrix(&matrixForSorting);

    return 0;
}