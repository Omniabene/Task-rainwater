#include "workerthread.h"
#include "singleton.h"
#include "matrixoperations.h"
#include <QRandomGenerator>
#include <QDebug>
#include <QTimer>

WorkerThread::WorkerThread()
{
}

//void WorkerThread::run()
//{
//    Singleton* singleton = Singleton::getInstance();
//    QList<SquareItem*> squares = singleton->getSquares();
//    // Генерация новых случайных значений для квадратов
//    for (int i=1;i<29;i++){

//        QVector<int> newValues;
//        for (SquareItem* square : squares)
//        {
//            int newValue = QRandomGenerator::global()->bounded(-10, 11);
//            newValues.append(newValue);
//        }

//        // Изменение сцены в главном потоке
//        QMetaObject::invokeMethod(this, "updateScene", Qt::QueuedConnection, Q_ARG(QVector<int>, newValues));
//        newValues.clear();
//        QThread::msleep(100);
//    }

//}

//void WorkerThread::updateScene(const QVector<int>& newValues)
//{
//    Singleton* singleton = Singleton::getInstance();
//    QList<SquareItem*> squares = singleton->getSquares();

//    // Обновление значений на сцене в основном потоке
//    for (int i = 0; i < squares.size(); ++i)
//    {
//        SquareItem* square = squares.at(i);
//        int newValue = newValues.at(i);
//        square->setText(QString::number(newValue));
//    }
//}


void WorkerThread::run()
{
    qDebug()<<"sadasdasdada";
    Singleton* singleton = Singleton::getInstance();

    // Получение количества столбцов и строк
    int N = singleton->get_N();
    int M = singleton->get_M();

    // Создание и заполнение исходной матрицы на основе данных в полях ввода
    QVector<QVector<int>> baseMatrix(M, QVector<int>(N));
    QList<SquareItem*> Squares = singleton->getSquares();
    QList<QGraphicsTextItem*> listLineEdits;
    int index = 0;
    for (int i = 0; i < M; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            SquareItem* Square = Squares.at(index);
            baseMatrix[i][j] = Square->getText().toInt();

            QGraphicsTextItem* textItem = Square->getTextItem();

            // Создаем новый QGraphicsTextItem и устанавливаем его свойства
            QGraphicsTextItem* newTextItem = new QGraphicsTextItem();
            newTextItem->setPlainText(textItem->toPlainText());
            newTextItem->setFont(textItem->font());
            // Установите остальные свойства по необходимости

            listLineEdits.append(newTextItem);

            ++index;
        }
    }
    qDebug()<<"sadasdasdadasdasdasdasdasa";
    singleton->set_listEdits(listLineEdits);
    // Создание рабочей матрицы и заполнение ее значениями по умолчанию
    QVector<QVector<int>> workMatrix(M, QVector<int>(N, 1000));

    N--;
    M--;

    // Вызов функции для обработки матрицы
    MatrixOperations::passThroughElementsMatrix(N, M, baseMatrix, workMatrix);
    qDebug()<<"123213213412421414";

    // Вызов функции для вывода результата
    MatrixOperations::outputResult(N, M, baseMatrix, workMatrix);
}

void WorkerThread::updateScene(const QVector<int>& newValues)
{
//    Singleton* singleton = Singleton::getInstance();
//    QList<SquareItem*> squares = singleton->getSquares();

//    // Обновление значений на сцене в основном потоке
//    for (int i = 0; i < squares.size(); ++i)
//    {
//        SquareItem* square = squares.at(i);
//        int newValue = newValues.at(i);
//        square->setText(QString::number(newValue));
//    }
}
