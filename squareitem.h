#ifndef SQUAREITEM_H
#define SQUAREITEM_H

#include <QGraphicsRectItem>
#include <QGraphicsTextItem>
#include <QTextDocument>
#include <QPointF>

/**
 * @brief Класс SquareItem - элемент квадрата.
 *
 * Наследуется от QGraphicsRectItem, чтобы представлять квадрат на графической сцене.
 * Также наследуется от QObject для поддержки сигналов и слотов.
 */
class SquareItem : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    /**
     * @brief Конструктор класса SquareItem.
     * @param x Координата X верхнего левого угла квадрата.
     * @param y Координата Y верхнего левого угла квадрата.
     * @param width Ширина квадрата.
     * @param height Высота квадрата.
     * @param index Индекс квадрата.
     */
    SquareItem(qreal x, qreal y, qreal width, qreal height, int index);

    /**
     * @brief Получить указатель на текстовый элемент.
     * @return Указатель на QGraphicsTextItem.
     */
    QGraphicsTextItem* getTextItem() const;

    /**
     * @brief Получить текст, связанный с квадратом.
     * @return Текстовая строка.
     */
    QString getText() const;

    /**
     * @brief Установить текст для квадрата.
     * @param text Текстовая строка для установки.
     */
    void setText(const QString& text);

    /**
     * @brief Установить размер текста.
     * @param size Размер текста.
     */
    void setTextSize(int size);

    /**
     * @brief Центрировать текст внутри квадрата.
     */
    void centerText();

    /**
     * @brief Получить индекс квадрата.
     * @return Целочисленное значение индекса.
     */
    int getIndex() const;

protected:
    /**
     * @brief Обработчик события наведения мыши на квадрат.
     * @param event Указатель на событие наведения мыши.
     */
    void hoverEnterEvent(QGraphicsSceneHoverEvent* event) override;

    /**
     * @brief Обработчик события ухода мыши с квадрата.
     * @param event Указатель на событие наведения мыши.
     */
    void hoverLeaveEvent(QGraphicsSceneHoverEvent* event) override;

private:
    QGraphicsTextItem* textItem; // Текстовый элемент для отображения текста внутри квадрата.
    QGraphicsTextItem* infoTextItem; // [TODO: Объясните назначение infoTextItem, если это требуется.]
    int squareIndex; // Индекс квадрата.
};

#endif // SQUAREITEM_H
