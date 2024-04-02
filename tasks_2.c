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

int cmp_long_long(const void *pa, const void *pb) {
    long long a = *(const long long *)pa;
    long long b = *(const long long *)pb;
    return (a > b) - (a < b);
}

int countNUnique(long long *a, int n) {
    if (n <= 0) return 0;

    int unique = 1;
    for (int i = 1; i < n; i++) {
        if (a[i] != a[i - 1]) {
            unique++;
        }
    }
    return unique;
}

int countEqClassesByRowsSum(matrix m) {
    // Создание массива для хранения сумм строк
    long long *rowSums = (long long *)malloc(m.nRows * sizeof(long long));

    // Вычисление сумм строк
    for (int i = 0; i < m.nRows; i++) {
        rowSums[i] = 0;
        for (int j = 0; j < m.nCols; j++) {
            rowSums[i] += m.values[i][j];
        }
    }

    // Сортировка сумм строк
    qsort(rowSums, m.nRows, sizeof(long long), cmp_long_long);

    // Подсчет уникальных сумм строк
    int uniqueSums = countNUnique(rowSums, m.nRows);

    // Освобождение памяти
    free(rowSums);

    return uniqueSums;
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

    // Создаем матрицу из примера
    matrix new = createMatrixFromArray((const int[]){
            7, 1,
            2, 7,
            5, 4,
            4, 3,
            1, 6,
            8, 0
    }, 6, 2);

    // Задание 10: Подсчитываем количество классов эквивалентных строк
    int classes = countEqClassesByRowsSum(new);

    // Выводим результат
    printf("Количество классов эквивалентных строк: %d\n", classes);

    // Освобождаем память, выделенную для матрицы
    freeMemMatrix(&new);

    return 0;
}