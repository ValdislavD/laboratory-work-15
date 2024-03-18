#include <stdio.h>
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

// Функция для вычисления суммы элементов в строке
int getSum(int *row, int nCols) {
    int sum = 0;
    for (int i = 0; i < nCols; i++) {
        sum += row[i];
    }
    return sum;
}

// Функция-критерий для сортировки столбцов по сумме элементов
int getColumnSum(int *col, int nRows) {
    int sum = 0;
    for (int i = 0; i < nRows; i++) {
        sum += col[i];
    }
    return sum;
}

void test_insertionSortRowsMatrixByRowCriteria() {
    matrix m = getMemMatrix(3, 3);
    m.values[0][0] = 3; m.values[0][1] = 2; m.values[0][2] = 1;
    m.values[1][0] = 6; m.values[1][1] = 5; m.values[1][2] = 4;
    m.values[2][0] = 9; m.values[2][1] = 8; m.values[2][2] = 7;

    insertionSortRowsMatrixByRowCriteria(m, getSum);

    // Проверка, что строки отсортированы по сумме элементов
    assert(getSum(m.values[0], m.nCols) <= getSum(m.values[1], m.nCols));
    assert(getSum(m.values[1], m.nCols) <= getSum(m.values[2], m.nCols));

    freeMemMatrix(&m);
}

void test_selectionSortColsMatrixByColCriteria() {
    matrix m = getMemMatrix(3, 3);
    m.values[0][0] = 1; m.values[0][1] = 4; m.values[0][2] = 7;
    m.values[1][0] = 2; m.values[1][1] = 5; m.values[1][2] = 8;
    m.values[2][0] = 3; m.values[2][1] = 6; m.values[2][2] = 9;

    selectionSortColsMatrixByColCriteria(m, getColumnSum);

    // Проверка, что столбцы отсортированы по сумме элементов
    assert(m.values[0][0] == 1 && m.values[1][0] == 2 && m.values[2][0] == 3);
    assert(m.values[0][1] == 4 && m.values[1][1] == 5 && m.values[2][1] == 6);
    assert(m.values[0][2] == 7 && m.values[1][2] == 8 && m.values[2][2] == 9);

    freeMemMatrix(&m);
}

void test_isSquareMatrix() {
    matrix m1 = getMemMatrix(3, 3); // Квадратная матрица
    matrix m2 = getMemMatrix(2, 3); // Прямоугольная матрица

    assert(isSquareMatrix(&m1) == true);
    assert(isSquareMatrix(&m2) == false);

    freeMemMatrix(&m1);
    freeMemMatrix(&m2);
}

void test_areTwoMatricesEqual() {
    matrix m1 = getMemMatrix(2, 2);
    matrix m2 = getMemMatrix(2, 2);
    matrix m3 = getMemMatrix(2, 2);

    // Заполнение матриц
    for (int i = 0; i < m1.nRows; i++) {
        for (int j = 0; j < m1.nCols; j++) {
            m1.values[i][j] = i * m1.nCols + j;
            m2.values[i][j] = i * m1.nCols + j;
            m3.values[i][j] = i * m1.nCols + j + 1;
        }
    }

    assert(areTwoMatricesEqual(&m1, &m2) == true);
    assert(areTwoMatricesEqual(&m1, &m3) == false);

    freeMemMatrix(&m1);
    freeMemMatrix(&m2);
    freeMemMatrix(&m3);
}

void test_isEMatrix() {
    matrix m1 = getMemMatrix(3, 3); // Единичная матрица
    matrix m2 = getMemMatrix(3, 3); // Единичная матрица, но с 0 на диагонали

    // Заполнение матриц
    for (int i = 0; i < m1.nRows; i++) {
        for (int j = 0; j < m1.nCols; j++) {
            m1.values[i][j] = (i == j) ? 1 : 0;
            m2.values[i][j] = (i == j) ? 0 : 1;
        }
    }

    assert(isEMatrix(&m1) == true);
    assert(isEMatrix(&m2) == false);

    freeMemMatrix(&m1);
    freeMemMatrix(&m2);
}

void test_isSymmetricMatrix() {
    // Создаем симметричную и несимметричную матрицы
    matrix m1 = getMemMatrix(3, 3); // Симметричная матрица
    matrix m2 = getMemMatrix(3, 3); // Несимметричная матрица

    // Заполнение симметричной матрицы
    m1.values[0][0] = 1; m1.values[0][1] = 2; m1.values[0][2] = 3;
    m1.values[1][0] = 2; m1.values[1][1] = 4; m1.values[1][2] = 5;
    m1.values[2][0] = 3; m1.values[2][1] = 5; m1.values[2][2] = 6;

    // Заполнение несимметричной матрицы
    m2.values[0][0] = 1; m2.values[0][1] = 2; m2.values[0][2] = 3;
    m2.values[1][0] = 4; m2.values[1][1] = 5; m2.values[1][2] = 6;
    m2.values[2][0] = 7; m2.values[2][1] = 8; m2.values[2][2] = 9;

    // Проверка
    assert(isSymmetricMatrix(&m1) == true);
    assert(isSymmetricMatrix(&m2) == false);

    // Освобождение памяти
    freeMemMatrix(&m1);
    freeMemMatrix(&m2);
}

void test_transposeSquareMatrix() {
    matrix m = getMemMatrix(3, 3);
    m.values[0][0] = 1; m.values[0][1] = 2; m.values[0][2] = 3;
    m.values[1][0] = 4; m.values[1][1] = 5; m.values[1][2] = 6;
    m.values[2][0] = 7; m.values[2][1] = 8; m.values[2][2] = 9;

    transposeSquareMatrix(&m);

    assert(m.values[0][0] == 1 && m.values[0][1] == 4 && m.values[0][2] == 7);
    assert(m.values[1][0] == 2 && m.values[1][1] == 5 && m.values[1][2] == 8);
    assert(m.values[2][0] == 3 && m.values[2][1] == 6 && m.values[2][2] == 9);

    freeMemMatrix(&m);
}

void test_transposeMatrix() {
    matrix m = getMemMatrix(2, 3);
    m.values[0][0] = 1; m.values[0][1] = 2; m.values[0][2] = 3;
    m.values[1][0] = 4; m.values[1][1] = 5; m.values[1][2] = 6;

    transposeMatrix(&m);

    assert(m.values[0][0] == 1 && m.values[0][1] == 4);
    assert(m.values[1][0] == 2 && m.values[1][1] == 5);
    assert(m.values[2][0] == 3 && m.values[2][1] == 6);

    freeMemMatrix(&m);
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
    test_selectionSortColsMatrixByColCriteria();
    test_isSquareMatrix();
    test_areTwoMatricesEqual();
    test_isEMatrix();
    test_isSymmetricMatrix();
    test_transposeSquareMatrix();
    test_transposeMatrix();
}

int main() {
    SetConsoleOutputCP(CP_UTF8);
    test();
    return 0;
}
