#include "matrixworker.h"
#include "singleton.h"
#include "matrixoperations.h"
#include <QRandomGenerator>
#include <QDebug>

MatrixWorker::MatrixWorker(QObject *parent) : QThread(parent)
{
}

void MatrixWorker::run()
{
    // Ваш код, который должен выполняться в параллельном потоке
    qDebug() << "Запуск параллельного потока";

    Singleton* singleton = Singleton::getInstance();

    // Получение количества столбцов и строк
    int N = singleton->get_N();
    int M = singleton->get_M();

    // Создание и заполнение исходной матрицы на основе данных в полях ввода
    QVector<QVector<int>> baseMatrix = singleton->getBaseMatrix();

    // Создание рабочей матрицы и заполнение ее значениями по умолчанию
    QVector<QVector<int>> workMatrix(M, QVector<int>(N, 1000));

    N--;
    M--;

    // Вызов функции для обработки матрицы
    MatrixOperations::passThroughElementsMatrix(N, M, baseMatrix, workMatrix);

    // Вызов функции для вывода результата
    MatrixOperations::outputResult(N, M, baseMatrix, workMatrix);


    //Обновление рабочей матрицы
    singleton->set_workMatrix(workMatrix);
    qDebug() << "Завершение параллельного потока";
    qRegisterMetaType<QVector<QVector<int>>>("QVector<QVector<int>>");

    emit finished();
}
