#include <assert.h>
#include "libs/data_structures/matrix/matrix.h"

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
}

int main() {
    test();
    return 0;
}
