#ifndef CUSTOMVALIDATOR_H
#define CUSTOMVALIDATOR_H

#include <QValidator>

/**
 * @brief Класс CustomValidator, реализующий пользовательский валидатор.
 *
 * Класс CustomValidator наследуется от QValidator и предоставляет функциональность
 * для валидации ввода пользовательских данных.
 */
class CustomValidator : public QValidator
{
public:
    /**
     * @brief Проверяет ввод пользователя и возвращает состояние валидации.
     *
     * Функция validate проверяет ввод пользователя и определяет, является ли он валидным
     * или невалидным.
     *
     * @param input Строка с вводом пользователя.
     * @param pos Позиция в строке ввода.
     * @return Состояние валидации (Acceptable, Invalid, Intermediate).
     */
    QValidator::State validate(QString& input, int& pos) const override;
};

#endif // CUSTOMVALIDATOR_H
