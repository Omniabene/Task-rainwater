#ifndef SCENEBUILDER_H
#define SCENEBUILDER_H

#include <QObject>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QLineEdit>
#include <QGraphicsProxyWidget>
#include <QRandomGenerator>
#include <QIntValidator>
#include <QWheelEvent>
#include "squareitem.h"

/**
 * @brief Класс SceneBuilder, представляющий построитель сцены.
 *
 * Класс SceneBuilder отвечает за создание и настройку графической сцены
 * на основе заданных параметров.
 */
class SceneBuilder : public QGraphicsView
{
    Q_OBJECT

public:
    /**
     * @brief Конструктор класса SceneBuilder.
     *
     * @param graphicsView Указатель на объект QGraphicsView.
     */
    SceneBuilder(QWidget *parent);

    /**
     * @brief Виртуальный деструктор класса SceneBuilder.
     */
    virtual ~SceneBuilder() {}

    /**
     * @brief Создает и настраивает сцену.
     *
     * Функция buildScene создает и настраивает графическую сцену
     * на основе заданных параметров.
     */
    void buildScene();
    void processSquareItems();
    void clearScene();

protected:
    /**
     * @brief Обработчик события прокрутки колесика мыши.
     *
     * @param event Событие колесика мыши.
     */
    void wheelEvent(QWheelEvent *event) override;

    /**
     * @brief Обработчик события нажатия кнопки мыши.
     *
     * @param event Событие нажатия кнопки мыши.
     */
    void mousePressEvent(QMouseEvent* event) override;

    /**
     * @brief Обработчик события перемещения мыши.
     *
     * @param event Событие перемещения мыши.
     */
    void mouseMoveEvent(QMouseEvent* event) override;

    /**
     * @brief Обработчик события отпускания кнопки мыши.
     *
     * @param event Событие отпускания кнопки мыши.
     */
    void mouseReleaseEvent(QMouseEvent* event) override;



signals:
    /**
     * @brief Сигнал для увеличения масштаба сцены.
     */
    void zoomIn();

    /**
     * @brief Сигнал для уменьшения масштаба сцены.
     */
    void zoomOut();

private:
    QGraphicsScene  m_scene; // Графическая сцена
    QVector<int> m_loadedCellIndices; // Индексы загруженных ячеек
    bool m_isLeftMouseButtonPressed = false; // Флаг нажатия левой кнопки мыши
    QList<SquareItem*> m_squares; // Список квадратных элементов на сцене

};

#endif // SCENEBUILDER_H

