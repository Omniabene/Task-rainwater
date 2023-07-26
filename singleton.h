#ifndef SINGLETON_H
#define SINGLETON_H

#include "squareitem.h"
#include <QMainWindow>
#include <QLineEdit>
#include <QGraphicsRectItem>

/**
 * @brief Класс Singleton, представляющий синглтон.
 *
 * Класс Singleton предоставляет единственный экземпляр класса
 * и доступ к его методам и данным.
 */
class Singleton {
private:
    uint N; /**< Количество столбцов. */
    uint M; /**< Количество строк. */
    QVector<int> m_loadedCellIndices; /**< Список индексов загруженных ячеек. */
    QList<SquareItem*> m_squares; /**< Список объектов SquareItem. */
    QVector<QVector<int>> m_baseMatrix; /**< Базовая матрица. */
    QVector<QVector<int>> m_workMatrix; /**< Рабочая матрица. */


    static Singleton* instance; /**< Указатель на единственный экземпляр класса. */

    /**
     * @brief Защищенный конструктор.
     *
     * Конструктор класса Singleton является защищенным для предотвращения
     * создания экземпляров класса напрямую.
     */
    Singleton() {}

public:
    /**
     * @brief Статический метод для получения единственного экземпляра класса.
     *
     * Метод getInstance возвращает указатель на единственный экземпляр класса
     * и создает его при первом вызове.
     *
     * @return Указатель на экземпляр класса Singleton.
     */
    static Singleton* getInstance();

    /**
     * @brief Устанавливает количество столбцов и строк.
     *
     * Метод set_NM устанавливает количество столбцов и строк в объекте Singleton.
     *
     * @param columns Количество столбцов.
     * @param rows Количество строк.
     */
    void set_NM(uint columns, uint rows);

    /**
     * @brief Устанавливает список индексов загруженных ячеек.
     *
     * Метод setLoadedCell устанавливает список индексов загруженных ячеек в объекте Singleton.
     *
     * @param m_loadedCellIndices Список индексов загруженных ячеек.
     */
    void setLoadedCell(QVector<int> m_loadedCellIndices);

    /**
     * @brief Устанавливает список объектов SquareItem.
     *
     * Метод set_squares устанавливает список объектов SquareItem в объекте Singleton.
     *
     * @param lineEdits Список объектов SquareItem.
     */
    void set_squares(QList<SquareItem*> lineEdits);

    /**
     * @brief Возвращает количество столбцов.
     *
     * Метод get_N возвращает количество столбцов,
     * установленное в объекте Singleton.
     *
     * @return Количество столбцов.
     */
    uint get_N();

    /**
     * @brief Возвращает количество строк.
     *
     * Метод get_M возвращает количество строк,
     * установленное в объекте Singleton.
     *
     * @return Количество строк.
     */
    uint get_M();

    /**
     * @brief Возвращает список индексов загруженных ячеек.
     *
     * Метод getLoadedCell возвращает список индексов загруженных ячеек,
     * установленный в объекте Singleton.
     *
     * @return Список индексов загруженных ячеек.
     */
    QVector<int> getLoadedCell();

    /**
     * @brief Возвращает список объектов SquareItem.
     *
     * Метод getSquares возвращает список объектов SquareItem,
     * установленный в объекте Singleton.
     *
     * @return Список объектов SquareItem.
     */
    QList<SquareItem*> getSquares();

    /**
     * @brief Очищает матрицы.
     *
     * Метод clearMatrix очищает базовую и рабочую матрицы в объекте Singleton.
     */
    void clearMatrix();

    /**
     * @brief Устанавливает базовую матрицу.
     *
     * Метод set_baseMatrix устанавливает базовую матрицу в объекте Singleton.
     *
     * @param baseMatrix Базовая матрица.
     */
    void set_baseMatrix(QVector<QVector<int>> baseMatrix);

    /**
     * @brief Возвращает базовую матрицу.
     *
     * Метод getBaseMatrix возвращает базовую матрицу,
     * установленную в объекте Singleton.
     *
     * @return Базовая матрица.
     */
    QVector<QVector<int>> getBaseMatrix();

    /**
     * @brief Устанавливает рабочую матрицу.
     *
     * Метод set_workMatrix устанавливает рабочую матрицу в объекте Singleton.
     *
     * @param workMatrix Рабочая матрица.
     */
    void set_workMatrix(QVector<QVector<int>> workMatrix);

    /**
     * @brief Возвращает рабочую матрицу.
     *
     * Метод getWorkMatrix возвращает рабочую матрицу,
     * установленную в объекте Singleton.
     *
     * @return Рабочая матрица.
     */
    QVector<QVector<int>> getWorkMatrix();
};

#endif // SINGLETON_H

