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

// Функция для нахождения минимального элемента в массиве
int getMin(int *a, int n) {
    int min = a[0];
    for (int i = 1; i < n; i++) {
        if (a[i] < min) {
            min = a[i];
        }
    }
    return min;
}

// Функция для упорядочивания столбцов матрицы по неубыванию минимальных элементов столбцов
void sortColsByMinElement(matrix *m) {
    int nCols = m->nCols;
    // Создаем временный массив для хранения минимальных элементов столбцов и их индексов
    int *minValues = (int *)malloc(nCols * sizeof(int));
    int *indices = (int *)malloc(nCols * sizeof(int));

    // Заполняем массивы минимальными значениями и индексами столбцов
    for (int j = 0; j < nCols; j++) {
        int *column = (int *)malloc(m->nRows * sizeof(int));
        for (int i = 0; i < m->nRows; i++) {
            column[i] = m->values[i][j];
        }
        minValues[j] = getMin(column, m->nRows);
        indices[j] = j;
        free(column);
    }

    // Сортируем массив индексов столбцов по соответствующим минимальным значениям
    for (int i = 1; i < nCols; i++) {
        int key = minValues[i];
        int index = indices[i];
        int j = i - 1;

        while (j >= 0 && minValues[j] > key) {
            minValues[j + 1] = minValues[j];
            indices[j + 1] = indices[j];
            j = j - 1;
        }
        minValues[j + 1] = key;
        indices[j + 1] = index;
    }

    // Создаем временную матрицу для хранения отсортированных столбцов
    matrix sorted = getMemMatrix(m->nRows, m->nCols);

    // Копируем столбцы в порядке, определенном отсортированным массивом индексов
    for (int j = 0; j < nCols; j++) {
        for (int i = 0; i < m->nRows; i++) {
            sorted.values[i][j] = m->values[i][indices[j]];
        }
    }

    // Освобождаем память от временных массивов
    free(minValues);
    free(indices);

    // Заменяем исходную матрицу на отсортированную
    freeMemMatrix(m);
    *m = sorted;
}

// Функция для вычисления произведения двух матриц
matrix mulMatrices(matrix m1, matrix m2) {
    assert(m1.nCols == m2.nRows); // Проверяем совместимость размеров матриц

    matrix result = getMemMatrix(m1.nRows, m2.nCols);

    for (int i = 0; i < m1.nRows; i++) {
        for (int j = 0; j < m2.nCols; j++) {
            result.values[i][j] = 0;
            for (int k = 0; k < m1.nCols; k++) {
                result.values[i][j] += m1.values[i][k] * m2.values[k][j];
            }
        }
    }

    return result;
}

// Функция для замены квадратной матрицы ее квадратом, если она симметрична
void getSquareOfMatrixIfSymmetric(matrix *m) {
    if (isSymmetricMatrix(m)) {
        // Создаем копию исходной матрицы
        matrix original = *m;

        // Вычисляем квадрат исходной матрицы
        matrix square = mulMatrices(original, original);

        // Освобождаем память, занятую исходной матрицей
        freeMemMatrix(m);

        // Заменяем исходную матрицу на ее квадрат
        *m = square;
    }
}

// Функция для проверки, все ли элементы в массиве уникальны
bool isUnique(long long *a, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (a[i] == a[j]) {
                return false; // Найдено повторяющееся значение
            }
        }
    }
    return true; // Все элементы уникальны
}

// Функция для вычисления суммы элементов в массиве
long long getSum(int *a, int n) {
    long long sum = 0;
    for (int i = 0; i < n; i++) {
        sum += a[i];
    }
    return sum;
}

// Функция для транспонирования матрицы, если суммы элементов строк различны
void transposeIfMatrixHasNotEqualSumOfRows(matrix m) {
    int nRows = m.nRows;
    long long *sums = (long long *)malloc(nRows * sizeof(long long));

    // Вычисляем суммы элементов строк матрицы
    for (int i = 0; i < nRows; i++) {
        sums[i] = getSum(m.values[i], m.nCols);
    }

    // Проверяем, все ли суммы элементов строк различны
    if (isUnique(sums, nRows)) {
        // Суммы элементов строк различны, транспонируем матрицу
        transposeMatrix(&m);
        printf("Матрица была транспонирована:\n");
        outputMatrix(m);
    } else {
        printf("Суммы элементов строк не различны, матрица остается без изменений.\n");
    }

    // Освобождаем память, выделенную под массив сумм
    free(sums);
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

    // Создаем и заполняем матрицу
    matrix myMatrix = createMatrixFromArray((const int[]){
            3, 5, 2, 4, 3, 3,
            2, 5, 1, 8, 2, 7,
            6, 1, 4, 4, 8, 3
    }, 3, 6);
    outputMatrix(myMatrix);

    // Задача 3: Упорядочить столбцы матрицы по неубыванию минимальных элементов столбцов
    sortColsByMinElement(&myMatrix);
    outputMatrix(myMatrix);

    // Освобождаем память от матрицы
    freeMemMatrix(&myMatrix);

    // Создаем и заполняем матрицу
    matrix my_Matrix = createMatrixFromArray((const int[]){
            1, 2, 3,
            2, 4, 5,
            3, 5, 6
    }, 3, 3);
    outputMatrix(my_Matrix);

    // Задача 4: Заменить квадратной матрицу ее квадратом, если она симметрична
    getSquareOfMatrixIfSymmetric(&my_Matrix);
    outputMatrix(my_Matrix);

    // Освобождаем память от матрицы
    freeMemMatrix(&myMatrix);

    // Создаем и заполняем матрицу
    matrix newMatrix = createMatrixFromArray((const int[]){
            1, 2, 3,
            4, 5, 6,
            7, 8, 9
    }, 3, 3);
    outputMatrix(myMatrix);

    // Задача 5: Транспонировать матрицу, если суммы элементов строк различны
    transposeIfMatrixHasNotEqualSumOfRows(newMatrix);

    // Освобождаем память от матрицы
    freeMemMatrix(&newMatrix);
    return 0;
}