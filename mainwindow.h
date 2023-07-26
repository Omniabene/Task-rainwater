#ifndef NEW_MACRO_NAME
#define NEW_MACRO_NAME

#include "scenebuilder.h"

#include <QMainWindow>
#include <QLineEdit>
#include <QGraphicsScene>
#include <QGraphicsWidget>
#include <QGraphicsTextItem>
#include <QGraphicsProxyWidget>
#include <QThread>
#include <QDebug>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

/**
 * @brief Класс MainWindow, представляющий главное окно приложения.
 *
 * Класс MainWindow наследуется от QMainWindow и предоставляет интерфейс
 * и функциональность главного окна приложения.
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief Конструктор класса MainWindow.
     *
     * @param parent Родительский виджет.
     */
    MainWindow(QWidget *parent = nullptr);

    /**
     * @brief Деструктор класса MainWindow.
     */
    ~MainWindow();

private:
    Ui::MainWindow *ui; /**< Указатель на объект интерфейса MainWindow. */
    SceneBuilder* m_sb; /**< Указатель на объект для построения сцены. */
    bool isRunning; /**< Флаг, указывающий, выполняется ли работа. */

private slots:
    // Слоты (обработчики событий)

    /**
     * @brief Обработчик события изменения текста.
     *
     * @param text Измененный текст.
     */
    void onTextChanged(const QString &text);

    /**
     * @brief Обработчик события нажатия на кнопку "pushButton".
     */
    void on_pushButton_clicked();

    /**
     * @brief Обработчик события нажатия на кнопку "pushButton_2".
     */
    void on_pushButton_2_clicked();

    /**
     * @brief Обработчик события нажатия на кнопку "pushButton_3".
     */
    void on_pushButton_3_clicked();

    /**
     * @brief Обработчик события завершения работы воркера (рабочего потока).
     */
    void onWorkerFinished();

    /**
     * @brief Бесконечный цикл для обновления интерфейса в фоновом режиме.
     */
    void yourMainLoop();

};

#endif // MAINWINDOW_H

