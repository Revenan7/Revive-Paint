#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include "drawingimage.h"
#include <QLabel>
class DrawingWidget;

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    void saveImage();

private:
    DrawingWidget *drawingWidget;
    DrawingImage *drawingImage;
    void createButtons();
    QPushButton *Save_Button;
    QLabel *imageLabel;
    void setWhite();
    void setBlack();
    void setBlue();
    void setRed();
};

#endif // MAINWINDOW_H
