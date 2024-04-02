#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
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

// Функция для сортировки строк матрицы по заданным критериям
void insertionSortRowsMatrixByRowCriteria(matrix m, int (*criteria)(int*, int)) {
    int nRows = m.nRows;
    int **rowValues = (int **)malloc(nRows * sizeof(int *)); // Временный массив для хранения указателей на строки и их значений критерия

    // Выделение памяти и вычисление значений критерия для каждой строки
    for (int i = 0; i < nRows; i++) {
        rowValues[i] = (int *)malloc((m.nCols + 1) * sizeof(int));
        rowValues[i][0] = criteria(m.values[i], m.nCols); // Значение критерия
        for (int j = 0; j < m.nCols; j++) {
            rowValues[i][j + 1] = m.values[i][j]; // Значения строки
        }
    }

    // Сортировка вставками на основе значений критерия
    for (int i = 1; i < nRows; i++) {
        int *key = rowValues[i];
        int j = i - 1;
        // Перемещение элементов rowValues[0..i-1], которые больше key, на одну позицию вперед относительно их текущей позиции
        while (j >= 0 && rowValues[j][0] > key[0]) {
            rowValues[j + 1] = rowValues[j];
            j = j - 1;
        }
        rowValues[j + 1] = key;
    }

    // Обновление значений строк матрицы
    for (int i = 0; i < nRows; i++) {
        for (int j = 0; j < m.nCols; j++) {
            m.values[i][j] = rowValues[i][j + 1];
        }
    }

    // Освобождение выделенной динамической памяти
    for (int i = 0; i < nRows; i++) {
        free(rowValues[i]);
    }
    free(rowValues);
}

void selectionSortColsMatrixByColCriteria(matrix m, int (*criteria)(int*, int)) {
    int nCols = m.nCols;
    int *colValues = (int *)malloc(nCols * sizeof(int)); // Временный массив для хранения значений критерия

    // Вычисление значений критерия для каждого столбца
    for (int j = 0; j < nCols; j++) {
        int *column = (int *)malloc(m.nRows * sizeof(int));
        for (int i = 0; i < m.nRows; i++) {
            column[i] = m.values[i][j];
        }
        colValues[j] = criteria(column, m.nRows);
        free(column);
    }

    // Сортировка выбором на основе значений критерия
    for (int i = 0; i < nCols - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < nCols; j++) {
            if (colValues[j] < colValues[minIndex]) {
                minIndex = j;
            }
        }
        if (minIndex != i) {
            // Обмен значений критерия
            int temp = colValues[i];
            colValues[i] = colValues[minIndex];
            colValues[minIndex] = temp;
            // Обмен столбцов
            for (int k = 0; k < m.nRows; k++) {
                int tempValue = m.values[k][i];
                m.values[k][i] = m.values[k][minIndex];
                m.values[k][minIndex] = tempValue;
            }
        }
    }

    free(colValues); // Освобождение выделенной динамической памяти
}

// Функция для проверки, является ли матрица квадратной
bool isSquareMatrix(matrix *m) {
    return m->nRows == m->nCols;
}

// Функция для проверки равенства двух матриц
bool areTwoMatricesEqual(matrix *m1, matrix *m2) {
    if (m1->nRows != m2->nRows || m1->nCols != m2->nCols) {
        return false;
    }

    for (int i = 0; i < m1->nRows; i++) {
        for (int j = 0; j < m1->nCols; j++) {
            if (m1->values[i][j] != m2->values[i][j]) {
                return false;
            }
        }
    }

    return true;
}

// Функция для проверки, является ли матрица единичной
bool isEMatrix(matrix *m) {
    if (!isSquareMatrix(m)) {
        return false;
    }

    for (int i = 0; i < m->nRows; i++) {
        for (int j = 0; j < m->nCols; j++) {
            if ((i == j && m->values[i][j] != 1) || (i != j && m->values[i][j] != 0)) {
                return false;
            }
        }
    }

    return true;
}

// Функция для проверки, является ли матрица симметричной
bool isSymmetricMatrix(matrix *m) {
    if (!isSquareMatrix(m)) {
        return false;
    }

    for (int i = 0; i < m->nRows; i++) {
        for (int j = 0; j < m->nCols; j++) {
            if (m->values[i][j] != m->values[j][i]) {
                return false;
            }
        }
    }

    return true;
}

// Функция для транспонирования квадратной матрицы
void transposeSquareMatrix(matrix *m) {
    // Проверяем, что матрица квадратная
    assert(isSquareMatrix(m));

    int size = m->nRows;
    for (int i = 0; i < size; i++) {
        for (int j = i + 1; j < size; j++) {
            // Обмениваем значения элементов симметрично относительно главной диагонали
            int temp = m->values[i][j];
            m->values[i][j] = m->values[j][i];
            m->values[j][i] = temp;
        }
    }
}

// Функция для транспонирования матрицы
void transposeMatrix(matrix *m) {
    int rows = m->nRows;
    int cols = m->nCols;
    // Создаем временную матрицу для хранения результата транспонирования
    matrix transposed = getMemMatrix(cols, rows);

    // Транспонируем исходную матрицу
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            transposed.values[j][i] = m->values[i][j];
        }
    }

    // Освобождаем память от исходной матрицы
    freeMemMatrix(m);

    // Присваиваем транспонированную матрицу исходной
    *m = transposed;
}

position getMinValuePos(matrix m) {
    position minPos;
    int minVal = m.values[0][0];
    minPos.rowIndex = 0;
    minPos.colIndex = 0;

    for (int i = 0; i < m.nRows; i++) {
        for (int j = 0; j < m.nCols; j++) {
            if (m.values[i][j] < minVal) {
                minVal = m.values[i][j];
                minPos.rowIndex = i;
                minPos.colIndex = j;
            }
        }
    }

    return minPos;
}

position getMaxValuePos(matrix m) {
    position maxPos;
    int maxVal = m.values[0][0];
    maxPos.rowIndex = 0;
    maxPos.colIndex = 0;

    for (int i = 0; i < m.nRows; i++) {
        for (int j = 0; j < m.nCols; j++) {
            if (m.values[i][j] > maxVal) {
                maxVal = m.values[i][j];
                maxPos.rowIndex = i;
                maxPos.colIndex = j;
            }
        }
    }

    return maxPos;
}

matrix createMatrixFromArray(const int *a, size_t nRows, size_t nCols) {
    matrix m = getMemMatrix(nRows, nCols);
    for (size_t i = 0; i < nRows; ++i) {
        memcpy(m.values[i], a + i * nCols, nCols * sizeof(int));
    }
    return m;
}

matrix *createArrayOfMatrixFromArray(const int *values, size_t nMatrices, size_t nRows, size_t nCols) {
    matrix *ms = getMemArrayOfMatrices(nMatrices, nRows, nCols);
    for (size_t i = 0; i < nMatrices; ++i) {
        for (size_t j = 0; j < nRows; ++j) {
            memcpy(ms[i].values[j], values + i * nRows * nCols + j * nCols, nCols * sizeof(int));
        }
    }
    return ms;
}

int countZeroRows(matrix m, size_t nRows, size_t nCols) {
    int count = 0;
    for (size_t i = 0; i < nRows; ++i) {
        int allZero = 1; // Флаг, указывающий, что все элементы строки равны нулю
        for (size_t j = 0; j < nCols; ++j) {
            if (m.values[i][j] != 0) {
                allZero = 0; // Если хотя бы один элемент не равен нулю, сбрасываем флаг
                break;
            }
        }
        if (allZero) {
            count++; // Увеличиваем счетчик, если все элементы строки равны нулю
        }
    }
    return count;
}

void insertionSortRowsMatrixByRowCriteriaF(matrix m, float (*criteria)(int *, int)) {
    int n = m.nRows;
    int i, j;
    for (i = 1; i < n; i++) {
        int *currentRow = m.values[i];
        float key = criteria(currentRow, m.nCols);
        j = i - 1;
        while (j >= 0 && criteria(m.values[j], m.nCols) > key) {
            swapRows(&m, j, j + 1);
            j = j - 1;
        }
        m.values[j + 1] = currentRow;
    }
}