#include "libs/data_structures/matrix/matrix.h"
#include <windows.h>

void swapRowsWithMinAndMax(matrix *m) {
    // Находим позиции минимального и максимального элементов
    position minPos = getMinValuePos(*m);
    position maxPos = getMaxValuePos(*m);

    // Поменять местами строки с минимальным и максимальным элементами
    swapRows(m, minPos.rowIndex, maxPos.rowIndex);
}

int main() {
    SetConsoleOutputCP(CP_UTF8);
    // Создаем и заполняем квадратную матрицу
    matrix squareMatrix = createMatrixFromArray((const int[]){5, 8, 3, 2}, 2, 2);
    outputMatrix(squareMatrix);

    // Задача 1: Поменять местами строки с минимальным и максимальным элементами
    swapRowsWithMinAndMax(&squareMatrix);
    outputMatrix(squareMatrix);

    return 0;
}