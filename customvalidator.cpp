#include "customvalidator.h"

// Проверка валидности ввода
// Возвращает состояние валидации QValidator::State
QValidator::State CustomValidator::validate(QString& input, int& pos) const
{
    // Если ввод пустой, возвращаем промежуточное состояние
    if (input.isEmpty())
        return QValidator::Intermediate;

    // Если первый символ равен '0', возвращаем недопустимое состояние
    if (input[0] == '0')
        return QValidator::Invalid;

    bool ok;
    int value = input.toInt(&ok);

    // Если значение корректно и находится в диапазоне от 1 до 1000,
    // возвращаем допустимое состояние
    if (ok && value >= 1 && value <= 1000)
        return QValidator::Acceptable;

    // Возвращаем недопустимое состояние
    return QValidator::Invalid;
}
