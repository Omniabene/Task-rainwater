#include "squareitem.h"
#include "singleton.h"
#include "mainwindow.h"
#include <QBrush>
#include <QGraphicsSceneHoverEvent>
#include <QFont>
#include <QTextOption>
#include <QGraphicsSceneMouseEvent>
#include <QCursor>
#include <QToolTip>
#include <QDebug>

// Конструктор квадратного элемента
SquareItem::SquareItem(qreal x, qreal y, qreal width, qreal height, int index)
    : QObject(), QGraphicsRectItem(x, y, width, height), squareIndex(index)
{
    setAcceptHoverEvents(true); // Включаем обработку событий наведения мыши

    // Создание текстового элемента для номера квадрата
    textItem = new QGraphicsTextItem(this);
    textItem->setTextInteractionFlags(Qt::TextEditorInteraction); // Включаем редактирование текста
    textItem->setTextWidth(width); // Установка ширины текстового элемента, чтобы ограничить текст в пределах квадрата
    textItem->setPos(x, y); // Устанавливаем позицию текстового элемента

    // Создание текстового элемента для отображения информации при наведении
    infoTextItem = new QGraphicsTextItem(this);
    infoTextItem->hide(); // Изначально скрываем его
}

// Возвращает указатель на текстовый элемент
QGraphicsTextItem* SquareItem::getTextItem() const
{
    return textItem;
}

// Возвращает текст, содержащийся в текстовом элементе
QString SquareItem::getText() const
{
    return textItem->toPlainText();
}

// Устанавливает текст в текстовом элементе
void SquareItem::setText(const QString& text)
{
    textItem->setPlainText(text);
}

// Устанавливает размер текста
void SquareItem::setTextSize(int size)
{
    QFont font = textItem->font();
    font.setPointSize(size);
    textItem->setFont(font);
}

// Выравнивает текст внутри квадрата по центру
void SquareItem::centerText()
{
    QTextOption option = textItem->document()->defaultTextOption();
    option.setAlignment(Qt::AlignCenter);
    option.setWrapMode(QTextOption::NoWrap);
    textItem->document()->setDefaultTextOption(option);
}

// Обработчик события наведения курсора на квадрат
void SquareItem::hoverEnterEvent(QGraphicsSceneHoverEvent* event)
{
    Singleton* singleton = Singleton::getInstance();
    QVector<QVector<int>> baseMatrix = singleton->getBaseMatrix();

    int desired_index = getIndex();
    int columns = baseMatrix[0].size();

    int row_index = desired_index / columns;
    int column_index = desired_index % columns;

    // Получение глобальных координат курсора
    QPointF cursorPos = QCursor::pos();

    // Преобразуем глобальные координаты в координаты сцены
    QPointF scenePos = mapFromScene(cursorPos);

    // Отображение информации о числе в соответствующей ячейке при наведении
    QToolTip::showText(scenePos.toPoint(), QString::number(baseMatrix[row_index][column_index]));

    QGraphicsRectItem::hoverEnterEvent(event);
}

// Обработчик события ухода курсора с квадрата
void SquareItem::hoverLeaveEvent(QGraphicsSceneHoverEvent* event)
{
    infoTextItem->hide(); // Скрытие текстового элемента с информацией

    QGraphicsRectItem::hoverLeaveEvent(event);
}

// Возвращает индекс квадрата
int SquareItem::getIndex() const
{
    return squareIndex;
}
