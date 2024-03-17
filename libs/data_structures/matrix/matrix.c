#include <stdio.h>
#include <malloc.h>
#include "matrix.h"

matrix getMemMatrix(int nRows, int nCols) {
    int **values = (int **) malloc(sizeof(int*) * nRows);
    for (int i = 0; i < nRows; i++)
        values[i] = (int *) calloc(nCols, sizeof(int));
    return (matrix){values, nRows, nCols};
}

matrix *getMemArrayOfMatrices(int nMatrices, int nRows, int nCols) {
    matrix *ms = (matrix*) malloc(sizeof(matrix) * nMatrices);
    for (int i = 0; i < nMatrices; i++)
        ms[i] = getMemMatrix(nRows, nCols);
    return ms;
}

void freeMemMatrix(matrix *m) {
    if (m != NULL && m->values != NULL) {
        // Освобождаем память для каждой строки матрицы
        for (int i = 0; i < m->nRows; i++) {
            free(m->values[i]);
        }
        // Освобождаем память для массива указателей на строки
        free(m->values);
        m->values = NULL; // Обнуляем указатель, чтобы избежать ошибок
        m->nRows = 0;
        m->nCols = 0;
    }
}

void freeMemMatrices(matrix *ms, int nMatrices) {
    if (ms != NULL) {
        // Освобождаем память для каждой матрицы в массиве
        for (int i = 0; i < nMatrices; i++) {
            freeMemMatrix(&ms[i]);
        }
        // Освобождаем память для самого массива матриц
        free(ms);
    }
}

void inputMatrix(matrix *m) {
    printf("Введите элементы матрицы %dx%d:\n", m->nRows, m->nCols);
    for (int i = 0; i < m->nRows; i++) {
        for (int j = 0; j < m->nCols; j++) {
            scanf("%d", &m->values[i][j]);
        }
    }
}

void inputMatrices(matrix *ms, int nMatrices) {
    for (int k = 0; k < nMatrices; k++) {
        printf("Введите элементы матрицы %d:\n", k + 1);
        inputMatrix(&ms[k]);
    }
}

void outputMatrix(matrix m) {
    printf("Матрица %dx%d:\n", m.nRows, m.nCols);
    for (int i = 0; i < m.nRows; i++) {
        for (int j = 0; j < m.nCols; j++) {
            printf("%d ", m.values[i][j]);
        }
        printf("\n");
    }
}

void outputMatrices(matrix *ms, int nMatrices) {
    for (int k = 0; k < nMatrices; k++) {
        printf("Матрица %d:\n", k + 1);
        outputMatrix(ms[k]);
        printf("\n");
    }
}

void swapRows(matrix *m, int row1, int row2) {
    // Проверяем, что индексы не выходят за границы
    assert(row1 >= 0 && row1 < m->nRows);
    assert(row2 >= 0 && row2 < m->nRows);

    // Обмениваем указатели на строки
    int *temp = m->values[row1];
    m->values[row1] = m->values[row2];
    m->values[row2] = temp;
}

void swapColumns(matrix m, int j1, int j2) {
    // Проверяем, что индексы не выходят за границы
    assert(j1 >= 0 && j1 < m.nCols);
    assert(j2 >= 0 && j2 < m.nCols);

    // Обмениваем значения в колонках
    for (int i = 0; i < m.nRows; i++) {
        int temp = m.values[i][j1];
        m.values[i][j1] = m.values[i][j2];
        m.values[i][j2] = temp;
    }
}

// Функция для вычисления суммы элементов в строке
int getSum(int *row, int nCols) {
    int sum = 0;
    for (int i = 0; i < nCols; i++) {
        sum += row[i];
    }
    return sum;
}

// Функция для сортировки строк матрицы по заданным критериям
void insertionSortRowsMatrixByRowCriteria(matrix m, int (*criteria)(int*, int)) {
    int nRows = m.nRows;
    int *rowValues = (int *)malloc(nRows * sizeof(int)); // Временный массив для хранения значений критерия

    // Вычисление значений критерия для каждой строки
    for (int i = 0; i < nRows; i++) {
        rowValues[i] = criteria(m.values[i], m.nCols);
    }

    // Сортировка вставками на основе значений критерия
    for (int i = 1; i < nRows; i++) {
        int key = rowValues[i];
        int *keyRow = m.values[i];
        int j = i - 1;
        // Перемещение элементов rowValues[0..i-1] и m.values[0..i-1], которые больше key, на одну позицию вперед относительно их текущей позиции
        while (j >= 0 && rowValues[j] > key) {
            rowValues[j + 1] = rowValues[j];
            m.values[j + 1] = m.values[j];
            j = j - 1;
        }
        rowValues[j + 1] = key;
        m.values[j + 1] = keyRow;
    }

    free(rowValues); // Освобождение выделенной динамической памяти
}


