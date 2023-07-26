#ifndef MATRIXOPERATIONS_H
#define MATRIXOPERATIONS_H

#include <QVector>
#include <QMainWindow>
#include <iostream>

/**
 * @brief Класс для операций с матрицами.
 */
class MatrixOperations
{
public:
    /**
     * @brief Функция рекурсивно обрабатывает ячейку матрицы.
     *
     * @param x Координата x ячейки.
     * @param y Координата y ячейки.
     * @param lev Текущий уровень.
     * @param N Количество строк в матрице.
     * @param M Количество столбцов в матрице.
     * @param baseMatrix Исходная матрица.
     * @param workMatrix Рабочая матрица.
     */
    static void cell(int x, int y, int lev, const int& N, const int& M,
                     const QVector<QVector<int>>& baseMatrix,
                     QVector<QVector<int>>& workMatrix);

    /**
     * @brief Проходит через элементы матрицы и обрабатывает их с помощью функции cell.
     *
     * @param N Количество строк в матрице.
     * @param M Количество столбцов в матрице.
     * @param baseMatrix Базовая матрица.
     * @param workMatrix Рабочая матрица.
     */
    static void passThroughElementsMatrix(const int& N, const int& M,
                                          const QVector<QVector<int>>& baseMatrix,
                                          QVector<QVector<int>>& workMatrix);

    /**
     * @brief Выводит результат обработки матрицы.
     *
     * @param N Количество строк в матрице.
     * @param M Количество столбцов в матрице.
     * @param baseMatrix Базовая матрица.
     * @param workMatrix Рабочая матрица.
     */
    static void outputResult(const int& N, const int& M,
                             const QVector<QVector<int>>& baseMatrix,
                             const QVector<QVector<int>>& workMatrix);
};

#endif // MATRIXOPERATIONS_H
