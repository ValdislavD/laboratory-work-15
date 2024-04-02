#include <stdio.h>
#include "libs/data_structures/matrix/matrix.h"
#include <windows.h>
#include <math.h>

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

// Функция для вычисления расстояния от начала координат до точки
float getDistance(int *a, int n) {
    float distance = 0;
    for (int i = 0; i < n; i++) {
        distance += pow(a[i], 2);
    }
    return sqrt(distance);
}

// Функция для сортировки матрицы по неубыванию расстояний до начала координат
void sortByDistances(matrix m) {
    insertionSortRowsMatrixByRowCriteriaF(m, getDistance);
}

int main() {
    SetConsoleOutputCP(CP_UTF8);
    // Создаем и заполняем матрицу
    matrix m = createMatrixFromArray((const int[]){
            10, 7, 5, 6,
            3, 11, 8, 9,
            4, 1, 12, 2
    }, 3, 4);

    //Задание 8: Найти минимальный элемент матрицы в выделенной области:
    int min = getMinInArea(m);
    printf("Минимальный элемент в выделенной области: %d\n", min);
    // Освобождение памяти от матрицы
    freeMemMatrix(&m);

    // Создание матрицы с точками (пример)
    matrix points = createMatrixFromArray((const int[]){
            5, 2, 7,
            4, 1, 6,
            3, 8, 9
    }, 3, 3);

    // Задание 9: Сортировка точек по расстояниям до начала координат
    sortByDistances(points);

    // Вывод отсортированных точек
    printf("Точки, отсортированные по расстояниям до начала координат:\n");
    outputMatrix(points);

    // Освобождение памяти от матрицы
    freeMemMatrix(&points);

    return 0;
}