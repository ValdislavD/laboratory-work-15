#include <stdio.h>
#include "libs/data_structures/matrix/matrix.h"
#include <windows.h>

// Функция для нахождения минимального элемента в выделенной области
int getMinInArea(matrix m) {
    position maxPos = getMaxValuePos(m);
    int min = m.values[maxPos.rowIndex][maxPos.colIndex]; // Предполагаем, что минимальный элемент равен максимальному

    // Из этой позиции двигаемся вверх по столбцу до начала строки,
    // увеличивая количество выделенных элементов в каждом столбце на 1
    int count = 1;
    for (int i = maxPos.rowIndex - 1; i >= 0; i--) {
        count++;
        for (int j = maxPos.colIndex - count + 1; j <= maxPos.colIndex + count - 1 && j < m.nCols; j++) {
            if (j >= 0) {
                min = (m.values[i][j] < min) ? m.values[i][j] : min;
            }
        }
    }
    printf("\n");

    return min;
}

int main() {
    SetConsoleOutputCP(CP_UTF8);
    // Создаем и заполняем матрицу
    matrix m = createMatrixFromArray((const int[]){
            10, 7, 5, 6,
            3, 11, 8, 9,
            4, 1, 12, 2
    }, 3, 4);

    //Найти минимальный элемент матрицы в выделенной области:
    int min = getMinInArea(m);
    printf("Минимальный элемент в выделенной области: %d\n", min);

    return 0;
}