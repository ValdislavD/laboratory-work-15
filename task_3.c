#include <stdio.h>
#include "libs/data_structures/matrix/matrix.h"
#include <math.h>
#include <limits.h>
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

// Функция для вычисления скалярного произведения двух векторов
double getScalarProduct(int *a, int *b, int n) {
    double product = 0;
    for (int i = 0; i < n; i++) {
        product += a[i] * b[i];
    }
    return product;
}

// Функция для вычисления длины вектора
double getVectorLength(int *a, int n) {
    double length = 0;
    for (int i = 0; i < n; i++) {
        length += a[i] * a[i];
    }
    return sqrt(length);
}

// Функция для вычисления косинуса угла между двумя векторами
double getCosine(int *a, int *b, int n) {
    double scalarProduct = getScalarProduct(a, b, n);
    double lengthA = getVectorLength(a, n);
    double lengthB = getVectorLength(b, n);

    return scalarProduct / (lengthA * lengthB);
}

// Функция для определения индекса вектора с максимальным углом к заданному вектору
int getVectorIndexWithMaxAngle(matrix m, int *b) {
    int maxIndex = 0;
    double maxCosine = -1;

    for (int i = 0; i < m.nRows; i++) {
        double cosine = getCosine(m.values[i], b, m.nCols);
        if (cosine > maxCosine) {
            maxCosine = cosine;
            maxIndex = i;
        }
    }

    return maxIndex;
}

// Функция для вычисления скалярного произведения строки и столбца
long long getScalarProductRowAndCol(matrix m, int rowIdx, int colIdx) {
    long long product = 0;

    for (int i = 0; i < m.nCols; i++) {
        product += (long long)m.values[rowIdx][i] * m.values[i][colIdx];
    }

    return product;
}

// Функция для нахождения скалярного произведения строки с наибольшим элементом на столбец с наименьшим элементом
long long getSpecialScalarProduct(matrix m, int n) {
    int maxElement = INT_MIN;
    int minElement = INT_MAX;
    int maxRowIdx = 0;
    int minColIdx = 0;

    // Находим наибольший элемент и его строку
    for (int i = 0; i < m.nRows; i++) {
        for (int j = 0; j < m.nCols; j++) {
            if (m.values[i][j] > maxElement) {
                maxElement = m.values[i][j];
                maxRowIdx = i;
            }
        }
    }

    // Находим наименьший элемент и его столбец
    for (int j = 0; j < m.nCols; j++) {
        if (m.values[j][maxRowIdx] < minElement) {
            minElement = m.values[j][maxRowIdx];
            minColIdx = j;
        }
    }

    // Вычисляем скалярное произведение строки с наибольшим элементом на столбец с наименьшим элементом
    long long scalarProduct = getScalarProductRowAndCol(m, maxRowIdx, minColIdx);

    return scalarProduct;
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

    // Создаем и заполняем матрицу с координатами векторов
    matrix vectors = createMatrixFromArray((const int[]){
            1, 2, 3,
            4, 5, 6,
            7, 8, 9
    }, 3, 3);

    // Задаем вектор v
    int v[] = {2, 2, 2};

    //Задание 17: Определяем индекс вектора с максимальным углом к v
    int maxAngleIndex = getVectorIndexWithMaxAngle(vectors, v);

    // Выводим результат
    printf("Индекс вектора с максимальным углом к заданному вектору: %d\n", maxAngleIndex);

    // Освобождаем память, выделенную для матрицы
    freeMemMatrix(&vectors);

    // Создаем и заполняем матрицу
    matrix matrix1 = createMatrixFromArray((const int[]){
            1, 2, 3,
            4, 5, 6,
            7, 8, 9
    }, 3, 3);

    // Находим скалярное произведение строки с наибольшим элементом на столбец с наименьшим элементом
    long long specialScalarProduct = getSpecialScalarProduct(matrix1, matrix1.nRows);

    // Выводим результат
    printf("Скалярное произведение строки с наибольшим элементом на столбец с наименьшим элементом: %lld\n", specialScalarProduct);

    // Освобождаем память, выделенную для матрицы
    freeMemMatrix(&matrix1);

    return 0;
}
