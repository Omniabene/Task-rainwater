#include "singleton.h"
#include <QDebug>

// Инициализация статического члена класса
Singleton* Singleton::instance = nullptr;

// Получение единственного экземпляра класса Singleton
// Если экземпляр еще не был создан, происходит его создание
Singleton* Singleton::getInstance() {
    if (instance == nullptr) {
        instance = new Singleton();
    }
    return instance;
}

// Установка количества столбцов и строк
void Singleton::set_NM(uint columns, uint row) {
    N = columns;
    M = row;
}

// Установка списка объектов QLineEdit
void Singleton::setLoadedCell(QVector<int> loadedCell) {
    m_loadedCellIndices = loadedCell;
}


void Singleton::set_squares(QList<SquareItem *> squares){
    m_squares = squares;
}

// Получение количества столбцов
uint Singleton::get_N() {
    return N;
}

// Получение количества строк
uint Singleton::get_M() {
    return M;
}

// Получение списка объектов QLineEdit
QVector<int> Singleton::getLoadedCell() {
    return m_loadedCellIndices;
}


QList<SquareItem*> Singleton::getSquares() {
    return m_squares;
}

void Singleton::set_baseMatrix(QVector<QVector<int>> baseMatrix){
    m_baseMatrix = baseMatrix;
}
QVector<QVector<int>> Singleton::getBaseMatrix(){
    return m_baseMatrix;
}

void Singleton::set_workMatrix(QVector<QVector<int>> workMatrix){
    m_workMatrix = workMatrix;
}
QVector<QVector<int>> Singleton::getWorkMatrix(){
    return m_workMatrix;
}

