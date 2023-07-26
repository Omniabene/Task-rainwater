#include "matrixoperations.h"
#include "singleton.h"
#include <QDebug>
#include <QStack>
#include <QPair>


void MatrixOperations::cell(int x, int y, int lev, const int& N, const int& M,
                            const QVector<QVector<int>>& baseMatrix,
                            QVector<QVector<int>>& workMatrix)
{
    // Создаем стек для хранения информации о ячейке
    QStack<QPoint> stack;

    // Помещаем начальную ячейку и её текущий уровень в стек
    stack.push(QPoint(x, y));
    stack.push(QPoint(lev, lev));

    while (!stack.isEmpty())
    {
        // Извлекаем текущий уровень и координаты ячейки из стека
        int currentLevel = stack.pop().x();
        QPoint current = stack.pop();
        x = current.x();
        y = current.y();

        // Проверяем, находится ли ячейка в пределах матрицы
        if (x < 0 || y < 0 || x > N || y > M) {
            continue; // Пропускаем ячейку, если она вне матрицы
        }

        // Проверяем, достигнут ли текущий уровень или превышен ли он в рабочей матрице
        if ((workMatrix)[y][x] <= currentLevel) {
            continue; // Пропускаем ячейку, если уровень уже обновлен
        }

        // Обновляем текущий уровень, если он меньше значения в исходной матрице
        currentLevel = (currentLevel < baseMatrix[y][x]) ? baseMatrix[y][x] : currentLevel;

        // Устанавливаем текущий уровень в рабочей матрице
        workMatrix[y][x] = currentLevel;

        // Добавляем соседние ячейки и их текущие уровни в стек для дальнейшей обработки
        stack.push(QPoint(x - 1, y));
        stack.push(QPoint(currentLevel, currentLevel));
        stack.push(QPoint(x + 1, y));
        stack.push(QPoint(currentLevel, currentLevel));
        stack.push(QPoint(x, y - 1));
        stack.push(QPoint(currentLevel, currentLevel));
        stack.push(QPoint(x, y + 1));
        stack.push(QPoint(currentLevel, currentLevel));
    }
}



void MatrixOperations::passThroughElementsMatrix(const int& N, const int& M,
                               const QVector<QVector<int>>& baseMatrix,
                               QVector<QVector<int>>& workMatrix)
{
    // Проходим по верхней и нижней границам матрицы
    for (int i = 1; i <= M; i++) {
        cell(0, i, 0, N, M, baseMatrix, workMatrix);
        cell(N, i, 0, N, M, baseMatrix, workMatrix);
    }

    // Проходим по левой и правой границам матрицы
    for (int i = 1; i <= N; i++) {
        cell(i, 0, 0, N, M, baseMatrix, workMatrix);
        cell(i, M, 0, N, M, baseMatrix, workMatrix);
    }

    if (baseMatrix[0][0] < 0){
        workMatrix[0][0] = 0;
    }else
        workMatrix[0][0] =  baseMatrix[0][0];
}

// Функция для вывода результата и сравнения матриц
void MatrixOperations::outputResult(const int& N, const int& M,
                  const QVector<QVector<int>>& baseMatrix,
                  const QVector<QVector<int>>& workMatrix)
{
    Singleton* singleton = Singleton::getInstance();

    QList<SquareItem*> squares = singleton->getSquares();
    int index = 0;
    int summ = 0;
    for (int y = 0; y <= M; y++) {
        for (int x = 0; x <= N; x++) {
            summ += workMatrix[y][x] - baseMatrix[y][x];
            index++;
        }
    }
    std::cout << "RESULT = " << summ << std::endl;
}
