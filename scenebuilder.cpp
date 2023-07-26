#include "scenebuilder.h"
#include <QIntValidator>
#include "singleton.h"
#include "squareitem.h"

#include <iostream>


#include <QGraphicsTextItem>
#include <QGraphicsRectItem>
#include <QGraphicsSceneWheelEvent>
#include <QDebug>
#include <QFont>
#include <QCoreApplication>

// Конструктор класса SceneBuilder
SceneBuilder::SceneBuilder(QWidget *parent)
    : QGraphicsView(parent)
{
    // Установка настроек для QGraphicsView
    setScene(&m_scene);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setDragMode(QGraphicsView::ScrollHandDrag);

    // Включение отслеживания мыши и настройка обновления вида
    setMouseTracking(true);
    setViewportUpdateMode(QGraphicsView::FullViewportUpdate);

    // Установка сглаживания и оптимизации рендеринга
    setRenderHint(QPainter::Antialiasing);
    setRenderHint(QPainter::HighQualityAntialiasing);
    setOptimizationFlag(QGraphicsView::DontAdjustForAntialiasing);

    // Установка якоря трансформации под мышью
    setTransformationAnchor(QGraphicsView::AnchorUnderMouse);

    // Установка размера сцены
    m_scene.setSceneRect(0, 0, 1000, 1000);
    connect(&m_scene, &QGraphicsScene::sceneRectChanged, this, &SceneBuilder::buildScene);
}

// Метод для построения сцены (визуализация квадратов)
void SceneBuilder::buildScene()
{
    // Получение данных из Singleton
    Singleton* singleton = Singleton::getInstance();
    QVector<QVector<int>> baseMatrix = singleton->getBaseMatrix();
    QVector<QVector<int>> workMatrix = singleton->getWorkMatrix();

    int NColumns = singleton->get_N();
    int MRows = singleton->get_M();

    int squareSize = 65;
    int sceneWidth = NColumns * squareSize;
    int sceneHeight = MRows * squareSize;

    // Установка размера сцены
    m_scene.setSceneRect(0, 0, sceneWidth, sceneHeight);

    // Получение видимой области QGraphicsView
    QRectF visibleRect = mapToScene(viewport()->geometry()).boundingRect();


    // Вычисление видимой области в координатах сцены
    int left = qMax(static_cast<int>(visibleRect.left()) - (static_cast<int>(visibleRect.left()) % squareSize), 0);
    int top = qMax(static_cast<int>(visibleRect.top()) - (static_cast<int>(visibleRect.top()) % squareSize), 0);
    int right = qMin(static_cast<int>(visibleRect.right()), sceneWidth - 1);
    int bottom = qMin(static_cast<int>(visibleRect.bottom()), sceneHeight - 1);

    // Отрисовка квадратов в видимой области
    if (workMatrix.empty()) {
        // Отрисовка базовой матрицы, если workMatrix пустая
        for (int y = top; y <= bottom; y += squareSize) {
            for (int x = left; x <= right; x += squareSize) {
                int rowIndex = y / squareSize;
                int columnIndex = x / squareSize;
                int squareIndex = rowIndex * NColumns + columnIndex;
                if (!(std::find(m_loadedCellIndices.begin(), m_loadedCellIndices.end(), squareIndex) == m_loadedCellIndices.end())) {
                    continue;
                }

                // Создание и настройка квадратов для базовой матрицы
                SquareItem* square = new SquareItem(x, y, squareSize, squareSize, squareIndex);
                square->setBrush(QBrush(Qt::green));
                square->setTextSize(12);
                square->centerText();
                QGraphicsTextItem* textItem = square->getTextItem();
                int inputHeight = textItem->document()->size().height();
                textItem->setPos(x, y + (squareSize - inputHeight) / 2);
                square->setText(QString::number(baseMatrix[rowIndex][columnIndex]));
                m_squares.append(square);
                m_loadedCellIndices.push_back(squareIndex);
                m_scene.addItem(square);
                singleton->set_squares(m_squares);
            }
        }
    } else {
        // Отрисовка рабочей матрицы, если workMatrix не пустая
        for (int y = top; y <= bottom; y += squareSize) {
            for (int x = left; x <= right; x += squareSize) {
                int rowIndex = y / squareSize;
                int columnIndex = x / squareSize;
                int squareIndex = rowIndex * NColumns + columnIndex;
                if (!(std::find(m_loadedCellIndices.begin(), m_loadedCellIndices.end(), squareIndex) == m_loadedCellIndices.end())) {
                    continue;
                }

                // Создание и настройка квадратов для рабочей матрицы
                SquareItem* square = new SquareItem(x, y, squareSize, squareSize, squareIndex);
                square->setBrush(QBrush(Qt::green));
                square->setTextSize(12);
                square->centerText();
                square->getTextItem()->setTextInteractionFlags(Qt::NoTextInteraction);
                QGraphicsTextItem* textItem = square->getTextItem();
                int inputHeight = textItem->document()->size().height();
                textItem->setPos(x, y + (squareSize - inputHeight) / 2);
                if (workMatrix[rowIndex][columnIndex] != baseMatrix[rowIndex][columnIndex]) {
                    square->setBrush(QBrush(Qt::blue));
                }
                square->setText(QString::number(workMatrix[rowIndex][columnIndex]));
                m_squares.append(square);
                m_loadedCellIndices.push_back(squareIndex);
                m_scene.addItem(square);
                singleton->set_squares(m_squares);
            }
        }
    }
    singleton->setLoadedCell(m_loadedCellIndices);
}



void SceneBuilder::processSquareItems() {
    // Получаем список всех элементов на сцене

    QList<QGraphicsItem*> allItems = m_scene.items();
    Singleton* singleton = Singleton::getInstance();
    QVector<QVector<int>> baseMatrix = singleton->getBaseMatrix();

    // Перебираем каждый элемент и проверяем, является ли он экземпляром SquareItem
    for (QGraphicsItem* item : allItems) {
        SquareItem* squareItem = dynamic_cast<SquareItem*>(item);
        if (squareItem) {
            int index = squareItem->getIndex();
            int columns = baseMatrix[0].size();
            int row_index = index / columns;
            int column_index = index % columns;
            baseMatrix[row_index][column_index] = squareItem->getText().toInt();
            // Теперь вы можете делать с этими элементами, что вам нужно
            // Например, вы можете использовать index, textItem и infoTextItem
            // для выполнения определенных операций или обновления данных
        }
    }
    singleton->set_baseMatrix(baseMatrix);
}


void SceneBuilder::clearScene() {
    m_loadedCellIndices.clear();
    m_squares.clear();
    m_scene.clear();
    buildScene();

}


// Обработчик события прокрутки колеса мыши
void SceneBuilder::wheelEvent(QWheelEvent* event)
{
    int delta = event->angleDelta().y();

    if (delta > 0) {
        qreal newScaleFactor = transform().m11() * 1.1;
        if (newScaleFactor <= 2.0) {
            scale(1.1, 1.1);
            buildScene(); // Перестройка сцены при увеличении масштаба
        }
    } else if (delta < 0) {
        qreal newScaleFactor = transform().m11() * 0.9;
        if (newScaleFactor >= 0.5) {
            scale(0.9, 0.9);
            buildScene(); // Перестройка сцены при уменьшении масштаба
        }
    }

    event->accept();
}

// Обработчик события нажатия кнопки мыши
void SceneBuilder::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton) {
        m_isLeftMouseButtonPressed = true;
    }

    QGraphicsView::mousePressEvent(event);
}

// Обработчик события перемещения мыши
void SceneBuilder::mouseMoveEvent(QMouseEvent* event)
{
    if (m_isLeftMouseButtonPressed) {
        // Перерисовка сцены при перемещении мыши с нажатой левой кнопкой
        buildScene();
    }

    QGraphicsView::mouseMoveEvent(event);
}

// Обработчик события отпускания кнопки мыши
void SceneBuilder::mouseReleaseEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton) {
        m_isLeftMouseButtonPressed = false;
    }

    QGraphicsView::mouseReleaseEvent(event);
}


