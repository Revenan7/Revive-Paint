#include "mainwindow.h"
#include "drawingimage.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QWidget>
#include <QScreen>
#include <QGuiApplication>
#include <QFileDialog>
#include <QStandardPaths>
#include <QFrame>
#include <QLabel>
#include <QPixmap>
#include <QGridLayout>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    drawingImage = new DrawingImage(this);

    this->setStyleSheet("background-color: rgb(102, 102, 153);");
    this->setStyleSheet("QPushButton { background-color: #007ACC; color: white; }"
                        "QSlider::groove:horizontal { background: #444; }"
                        "QSlider::handle:horizontal { background: #007ACC; }");


    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);


    imageLabel = new QLabel(this);
    QString imagePath = "C:/Users/TheGolden/Desktop/Sourse/logo_NB.png";
    QPixmap w(imagePath);


    if (!w.isNull()) {
        imageLabel->setPixmap(w.scaled(100, 100, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    }

    QHBoxLayout *mainLayout = new QHBoxLayout(centralWidget);


    QVBoxLayout *leftLayout = new QVBoxLayout();


    leftLayout->addWidget(imageLabel, 0, Qt::AlignLeft | Qt::AlignTop);
    leftLayout->setContentsMargins(0, 10, 0, 0); // (left, top, right, bottom)

    // Создаем кнопки
    QPushButton *button1 = new QPushButton(this);
    QPushButton *button2 = new QPushButton(this);
    QPushButton *button3 = new QPushButton(this);
    QPushButton *button4 = new QPushButton(this);

    // Задаем размеры кнопок
    button1->setFixedSize(30, 30);
    button2->setFixedSize(30, 30);
    button3->setFixedSize(30, 30);
    button4->setFixedSize(30, 30);

    // Задаем стили для кнопок
    button1->setStyleSheet("background-color: #FFFFFF;");
    button2->setStyleSheet("background-color: #000000;");
    button3->setStyleSheet("background-color: #093453;");
    button4->setStyleSheet("background-color: #9D2C2C;");


    // Создаем сетку 2x2 для кнопок
    QGridLayout *gridLayout = new QGridLayout();
    gridLayout->addWidget(button1, 0, 0); // Первая строка, первый столбец
    gridLayout->addWidget(button2, 0, 1); // Первая строка, второй столбец
    gridLayout->addWidget(button3, 1, 0); // Вторая строка, первый столбец
    gridLayout->addWidget(button4, 1, 1); // Вторая строка, второй столбец

    // Добавляем сетку кнопок под изображением и выравниваем её по левому краю и сверху
    leftLayout->addLayout(gridLayout, Qt::AlignTop);
    leftLayout->setAlignment(gridLayout, Qt::AlignLeft | Qt::AlignTop);

    // Создаем кнопку Save и добавляем её в левую панель внизу
    Save_Button = new QPushButton("Save", this);
    leftLayout->addWidget(Save_Button, 0, Qt::AlignLeft | Qt::AlignBottom);

    gridLayout->setContentsMargins(15   , 20, 0, 0); // (left, top, right, bottom)


    // Добавляем левую панель (с изображением, кнопками и Save) в основной макет
    mainLayout->addLayout(leftLayout); // Добавляем панель с кнопками и изображением слева
    mainLayout->addWidget(drawingImage); // Добавляем drawingImage в макет

    // Подключаем сигнал кнопки к слоту
    connect(Save_Button, &QPushButton::clicked, this, &MainWindow::saveImage);
    connect(button1, &QPushButton::clicked, this, &MainWindow::setWhite);
    connect(button2, &QPushButton::clicked, this, &MainWindow::setBlack);
    connect(button3, &QPushButton::clicked, this, &MainWindow::setBlue);
    connect(button4, &QPushButton::clicked, this, &MainWindow::setRed);


    showMaximized();
}
void MainWindow::setWhite()
{
    drawingImage->PenColor = "#FFFFFF";
}
void MainWindow::setBlack()
{
    drawingImage->PenColor = "#000000";
}
void MainWindow::setBlue()
{
    drawingImage->PenColor = "#093453";
}
void MainWindow::setRed()
{
    drawingImage->PenColor = "#9D2C2C";
}

void MainWindow::saveImage()
{
    QString path = "C:/Users/TheGolden/Desktop/qPaint";
    QString filePath = QFileDialog::getSaveFileName(this, "Сохранить изображение", path, "Images (*.png *.jpg)");

    if (!filePath.isEmpty()) {
        if (drawingImage->GetImage().save(filePath)) {
            qDebug() << "Изображение сохранено:" << filePath;
        } else {
            qDebug() << "Ошибка при сохранении изображения";
        }
    }
}
