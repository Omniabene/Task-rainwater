#ifndef MATRIXWORKER_H
#define MATRIXWORKER_H

#include <QThread>

/**
 * @brief Класс для работы с матрицами в отдельном потоке.
 *
 * Этот класс наследуется от QThread, чтобы выполнять работу с матрицами
 * в отдельном потоке, не блокируя главный поток приложения.
 */
class MatrixWorker : public QThread
{
    Q_OBJECT

public:
    /**
     * @brief Конструктор класса MatrixWorker.
     *
     * @param parent Указатель на родительский объект (по умолчанию nullptr).
     */
    explicit MatrixWorker(QObject *parent = nullptr);

signals:
    /**
     * @brief Сигнал о завершении работы.
     */
    void finished();

public slots:
    /**
     * @brief Реализация основного потока выполнения.
     *
     * Этот метод будет выполняться в отдельном потоке при вызове start().
     */
    void run();
};

#endif // MATRIXWORKER_H

