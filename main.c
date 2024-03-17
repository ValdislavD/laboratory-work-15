#include <assert.h>
#include "libs/data_structures/matrix/matrix.h"
#include <windows.h>

void test_getMemMatrix1() {
    matrix m = getMemMatrix(2, 3);
    assert(m.nRows == 2);
    assert(m.nCols == 3);
    // Дополнительные проверки, если необходимо
    for (int i = 0; i < m.nRows; i++) {
        for (int j = 0; j < m.nCols; j++) {
            assert(m.values[i][j] == 0); // Проверяем инициализацию нулями
        }
    }
    freeMemMatrix(&m);
}

void test_getMemArrayOfMatrices1() {
    int nMatrices = 2;
    int nRows = 3;
    int nCols = 4;
    matrix *ms = getMemArrayOfMatrices(nMatrices, nRows, nCols);
    assert(ms != NULL);
    for (int i = 0; i < nMatrices; i++) {
        assert(ms[i].nRows == nRows);
        assert(ms[i].nCols == nCols);
        // Дополнительные проверки, если необходимо
        for (int j = 0; j < nRows; j++) {
            for (int k = 0; k < nCols; k++) {
                assert(ms[i].values[j][k] == 0); // Проверяем инициализацию нулями
            }
        }
        freeMemMatrix(&ms[i]);
    }
    freeMemMatrices(ms, nMatrices);
}

void test_freeMemMatrix() {
    // Создаем матрицу
    matrix m = getMemMatrix(2, 3);

    // Освобождаем память для матрицы
    freeMemMatrix(&m);

    // Проверяем, что матрица была освобождена
    assert(m.values == NULL);
    assert(m.nRows == 0);
    assert(m.nCols == 0);
}

void test_freeMemMatrices() {
    // Создаем массив матриц
    int nMatrices = 2;
    int nRows = 3;
    int nCols = 4;
    matrix *ms = getMemArrayOfMatrices(nMatrices, nRows, nCols);

    // Освобождаем память для массива матриц
    freeMemMatrices(ms, nMatrices);
}

void test_inputOutputFunctions() {
    matrix m = getMemMatrix(2, 2);
    inputMatrix(&m);
    printf("Введенная матрица:\n");
    outputMatrix(m);
    freeMemMatrix(&m);
}

void test_inputOutputArrayFunctions() {
    int nMatrices = 2;
    int nRows = 3;
    int nCols = 3;
    matrix *ms = getMemArrayOfMatrices(nMatrices, nRows, nCols);
    inputMatrices(ms, nMatrices);
    printf("Введенные матрицы:\n");
    outputMatrices(ms, nMatrices);
    freeMemMatrices(ms, nMatrices);
}

void test_swapRows() {
    matrix m = getMemMatrix(3, 3);
    m.values[0][0] = 1;
    m.values[0][1] = 2;
    m.values[0][2] = 3;
    m.values[1][0] = 4;
    m.values[1][1] = 5;
    m.values[1][2] = 6;
    m.values[2][0] = 7;
    m.values[2][1] = 8;
    m.values[2][2] = 9;

    swapRows(&m, 0, 2);

    assert(m.values[0][0] == 7);
    assert(m.values[0][1] == 8);
    assert(m.values[0][2] == 9);
    assert(m.values[2][0] == 1);
    assert(m.values[2][1] == 2);
    assert(m.values[2][2] == 3);

    freeMemMatrix(&m);
}

void test_swapColumns() {
    matrix m = getMemMatrix(3, 3);
    m.values[0][0] = 1;
    m.values[0][1] = 2;
    m.values[0][2] = 3;
    m.values[1][0] = 4;
    m.values[1][1] = 5;
    m.values[1][2] = 6;
    m.values[2][0] = 7;
    m.values[2][1] = 8;
    m.values[2][2] = 9;

    swapColumns(m, 0, 2);

    assert(m.values[0][0] == 3);
    assert(m.values[1][0] == 6);
    assert(m.values[2][0] == 9);
    assert(m.values[0][2] == 1);
    assert(m.values[1][2] == 4);
    assert(m.values[2][2] == 7);

    freeMemMatrix(&m);
}

void test_insertionSortRowsMatrixByRowCriteria() {
    // Создание примера матрицы
    matrix m;
    m.nRows = 3;
    m.nCols = 3;
    m.values = (int **)malloc(m.nRows * sizeof(int *));
    for (int i = 0; i < m.nRows; i++) {
        m.values[i] = (int *)malloc(m.nCols * sizeof(int));
    }

    // Инициализация значений матрицы
    m.values[0][0] = 3; m.values[0][1] = 2; m.values[0][2] = 1;
    m.values[1][0] = 6; m.values[1][1] = 5; m.values[1][2] = 4;
    m.values[2][0] = 9; m.values[2][1] = 8; m.values[2][2] = 7;

    // Сортировка строк на основе суммы элементов в каждой строке
    insertionSortRowsMatrixByRowCriteria(m, getSum);

    // Проверка отсортированной матрицы
    assert(m.values[0][0] == 1 && m.values[0][1] == 2 && m.values[0][2] == 3);
    assert(m.values[1][0] == 4 && m.values[1][1] == 5 && m.values[1][2] == 6);
    assert(m.values[2][0] == 7 && m.values[2][1] == 8 && m.values[2][2] == 9);

    // Освобождение выделенной динамической памяти
    for (int i = 0; i < m.nRows; i++) {
        free(m.values[i]);
    }
    free(m.values);
}

void test_freeMemFunctions() {
    test_freeMemMatrix();
    test_freeMemMatrices();
}

void test_getMemFunctions() {
    test_getMemMatrix1();
    test_getMemArrayOfMatrices1();
}

void test() {
    // Добавляем сюда другие тесты, если необходимо
    test_getMemFunctions();
    test_freeMemFunctions();
    test_inputOutputFunctions();
    test_inputOutputArrayFunctions();
    test_swapRows();
    test_swapColumns();
    test_insertionSortRowsMatrixByRowCriteria();
}

int main() {
    SetConsoleOutputCP(CP_UTF8);
    test();
    return 0;
}
