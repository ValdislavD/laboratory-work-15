#include <stdio.h>
#include "libs/data_structures/matrix/matrix.h"
#include <math.h>
#include <stdbool.h>
#include <windows.h>

// Функция для вычисления нормы матрицы (максимум абсолютных значений элементов)
float matrixNorm(matrix m) {
    float maxAbsValue = 0;
    for (int i = 0; i < m.nRows; i++) {
        for (int j = 0; j < m.nCols; j++) {
            float absValue = fabs(m.values[i][j]);
            if (absValue > maxAbsValue) {
                maxAbsValue = absValue;
            }
        }
    }
    return maxAbsValue;
}

// Функция для поиска матрицы с наименьшей нормой в массиве матриц
matrix findMatrixWithMinNorm(matrix *ms, int nMatrices) {
    matrix minNormMatrix = ms[0];
    float minNorm = matrixNorm(minNormMatrix);
    for (int i = 1; i < nMatrices; i++) {
        float norm = matrixNorm(ms[i]);
        if (norm < minNorm) {
            minNorm = norm;
            minNormMatrix = ms[i];
        }
    }
    return minNormMatrix;
}

// Функция для вывода матрицы с наименьшей нормой
void printMatrixWithMinNorm(matrix *ms, int nMatrices) {
    matrix minNormMatrix = findMatrixWithMinNorm(ms, nMatrices);
    printf("Матрица с наименьшей нормой:\n");
    outputMatrix(minNormMatrix);
}

// Функция для определения минимального из двух чисел
int min2(int a, int b) {
    return (a < b) ? a : b;
}

// Функция для определения количества "особых" элементов матрицы
int getNSpecialElement2(matrix m) {
    int nRows = m.nRows;
    int nCols = m.nCols;
    int count = 0;

    // Проходим по каждому элементу матрицы
    for (int i = 0; i < nRows; i++) {
        for (int j = 0; j < nCols; j++) {
            bool isSpecial = true;

            // Проверяем, что все элементы в строке слева от текущего элемента меньше него
            for (int k = 0; k < j; k++) {
                if (m.values[i][k] >= m.values[i][j]) {
                    isSpecial = false;
                    break;
                }
            }

            // Проверяем, что все элементы в строке справа от текущего элемента больше него
            for (int k = j + 1; k < nCols; k++) {
                if (m.values[i][k] <= m.values[i][j]) {
                    isSpecial = false;
                    break;
                }
            }

            // Если текущий элемент "особый", увеличиваем счетчик
            if (isSpecial) {
                count++;
            }
        }
    }

    return count;
}

int main() {
    SetConsoleOutputCP(CP_UTF8);
    // Пример массива целочисленных квадратных матриц
    matrix matrices[] = {
            createMatrixFromArray((const int[]){
                    1, 2, 3,
                    4, 5, 6,
                    7, 8, 9
            }, 3, 3),
            createMatrixFromArray((const int[]){
                    -3, 4, -5,
                    6, -7, 8,
                    -9, 10, -11
            }, 3, 3),
            createMatrixFromArray((const int[]){
                    0, -2, 3,
                    4, 0, -6,
                    -8, 9, 0
            }, 3, 3)
    };

    //Задание 15: Вывод матрицы с наименьшей нормой
    printMatrixWithMinNorm(matrices, sizeof(matrices) / sizeof(matrices[0]));

    // Освобождение памяти, выделенной для матриц
    for (int i = 0; i < sizeof(matrices) / sizeof(matrices[0]); i++) {
        freeMemMatrix(&matrices[i]);
    }

    // Создаем и заполняем матрицу
    matrix m = createMatrixFromArray((const int[]){
            2, 3, 5, 5, 4,
            6, 2, 3, 8, 12,
            12, 12, 2, 1, 2
    }, 3, 5);

    //Задание 16: Определяем количество "особых" элементов в матрице
    int specialElements = getNSpecialElement2(m);

    // Выводим результат
    printf("Количество \"особых\" элементов в матрице: %d\n", specialElements);

    // Освобождаем память, выделенную для матрицы
    freeMemMatrix(&m);

    return 0;
}
