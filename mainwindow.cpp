#include "mainwindow.h"
#include "matrixworker.h"
#include "./ui_mainwindow.h"
#include "squareitem.h"
#include "singleton.h"
#include "customvalidator.h"
#include "scenebuilder.h"


// Конструктор главного окна
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow),
      isRunning(false)
{
    ui->setupUi(this);
    ui->pushButton_2->hide();

    // Создание и установка валидатора для полей ввода
    const QRegExp  rx = QRegExp("");
    QRegExpValidator re(rx);

    CustomValidator* customValidator = new CustomValidator();
    ui->lineEdit_N->setValidator(customValidator);
    ui->lineEdit_M->setValidator(customValidator);

    // Соединение сигналов и слотов для обработки изменений в полях ввода
    connect(ui->lineEdit_N, &QLineEdit::textChanged,
            this, &MainWindow::onTextChanged);
    connect(ui->lineEdit_M, &QLineEdit::textChanged,
            this, &MainWindow::onTextChanged);

    // Создание и добавление m_sb (SceneBuilder) виджета в окно
    m_sb = new SceneBuilder(ui->widget);
    ui->gridLayout_2->addWidget(m_sb);
}

// Деструктор главного окна
MainWindow::~MainWindow()
{
    delete ui;
}

// Слот, вызываемый при изменении текста в полях ввода
void MainWindow::onTextChanged(const QString &text)
{
    // Проверка, заполнены ли поля ввода
    if(!ui->lineEdit_N->text().isEmpty() && !ui->lineEdit_M->text().isEmpty()){
        ui->pushButton->setEnabled(true);
        ui->pushButton_3->setEnabled(true);
    }
    else{
        ui->pushButton->setEnabled(false);
        ui->pushButton_3->setEnabled(false);
    }
}

// Обработчик клика на кнопке "Ручной ввод"
void MainWindow::on_pushButton_clicked()
{
    ui->pushButton_2->show();
    ui->pushButton->setEnabled(false);
    ui->pushButton_3->setEnabled(false);
    ui->lineEdit_N->setEnabled(false);
    ui->lineEdit_M->setEnabled(false);

    // Получение количества столбцов и строк из полей ввода
    uint NColumns = ui->lineEdit_N->text().toInt();
    uint MRow = ui->lineEdit_M->text().toInt();



    // Получение экземпляра класса Singleton и установка NColumns и MRow
    Singleton* singleton = Singleton::getInstance();
    singleton->set_NM(NColumns, MRow);

    QVector<QVector<int>> baseMatrix(MRow, QVector<int>(NColumns, 0));
    singleton->set_baseMatrix(baseMatrix);

    m_sb->buildScene();
}

void MainWindow::on_pushButton_2_clicked()
{
    //Обновление базовой матрицы со всеми изменениями на сцене
    m_sb->processSquareItems();

    // Создание и запуск потока для выполнения вычислений в фоновом режиме
    if (!isRunning) {
        isRunning = true;

        // Создание и запуск потока
        QThread* thread = new QThread();
        MatrixWorker* worker = new MatrixWorker();
        worker->moveToThread(thread);
        qRegisterMetaType<QVector<QVector<int>>>("QVector<QVector<int>>");
        connect(thread, SIGNAL(started()), worker, SLOT(run()));
        connect(worker, SIGNAL(finished()),thread, SLOT(quit()));
        connect(worker, SIGNAL(finished()),worker, SLOT(deleteLater()));
        connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
        connect(worker, SIGNAL(finished()), this, SLOT(onWorkerFinished()));
        // Запуск потока
        thread->start();
        // Запуск бесконечного цикла с обновлением интерфейса
        yourMainLoop();
    }

    //Очистка сцены
    m_sb->clearScene();

    Singleton* singleton = Singleton::getInstance();
    QVector<QVector<int>> baseMatrix = singleton->getBaseMatrix();
    QVector<int> loadedCellIndices = singleton->getLoadedCell();
    QList<SquareItem*> squares= singleton->getSquares();

    //Отображение на сцене полученой матрицы
    QVector<QVector<int>> workMatrix = singleton->getWorkMatrix();
    int sIndex = 0;
    int index = 0;
    for (int y = 0; y <= baseMatrix.size()-1; y++) {
        for (int x = 0; x <= baseMatrix[0].size()-1; x++) {
            if (loadedCellIndices.contains(index)){
                SquareItem* square = squares.at(sIndex);

                // Обновление значений ячеек
                if(workMatrix[y][x] != baseMatrix[y][x]){
                    square->setBrush(QBrush(Qt::blue));
                    square->setText(QString::number(workMatrix[y][x]));
                } else {
                    square->setText(QString::number(workMatrix[y][x]));
                }
                square->getTextItem()
                        ->setTextInteractionFlags(Qt::NoTextInteraction);
                sIndex++;

            }
            index++;
        }
    }
}

void MainWindow::onWorkerFinished()
{
    isRunning = false;
}

// Бесконечный цикл для обновления интерфейса в фоновом режиме
void MainWindow::yourMainLoop()
{
    Singleton* singleton = Singleton::getInstance();
    QList<SquareItem*> squares = singleton->getSquares();

    // Бесконечный цикл, выполняющийся пока isRunning установлено в true
    while (isRunning) {
        for (SquareItem* square : squares)
        {
            // Генерация случайного значения для каждой ячейки
            int newValue = QRandomGenerator::global()->bounded(-10, 11);
            square->setText(QString::number(newValue));
        }

        // Обновление интерфейса
        QApplication::processEvents();
    }

}

// Обработчик клика на кнопке "Рандом"
void MainWindow::on_pushButton_3_clicked()
{
    // Показать кнопку "Решить" и отключить кнопки "Ручной ввод" и "Рандом"
    ui->pushButton_2->show();
    ui->pushButton->setEnabled(false);
    ui->pushButton_3->setEnabled(false);
    ui->lineEdit_N->setEnabled(false);
    ui->lineEdit_M->setEnabled(false);

    // Получение количества столбцов и строк из полей ввода
    uint NColumns = ui->lineEdit_N->text().toInt();
    uint MRow = ui->lineEdit_M->text().toInt();

    // Получение экземпляра класса Singleton и установка NColumns и MRow
    Singleton* singleton = Singleton::getInstance();
    singleton->set_NM(NColumns, MRow);

    // Создание и заполнение базовой матрицы случайными значениями
    QVector<QVector<int>> baseMatrix(MRow, QVector<int>(NColumns, 0));
    for (int i = 0; i < MRow; ++i) {
        for (int j = 0; j < NColumns; ++j) {
            int randomValue = QRandomGenerator::global()->bounded(-10, 11);
            baseMatrix[i][j] = randomValue;
        }
    }

    // Установка базовой матрицы и перестроение сцены
    singleton->set_baseMatrix(baseMatrix);
    m_sb->buildScene();
}
