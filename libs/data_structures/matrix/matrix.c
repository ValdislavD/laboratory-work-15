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