#include "drawingimage.h"
#include <QMouseEvent>
#include <QPainter>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QKeyEvent>
#include <QDebug> // Для вывода дельты в консоль

DrawingImage::DrawingImage(QWidget *parent)
    : QGraphicsView(parent), drawing(false), scaleFactor(1)
{
    // Создаем сцену

    scene = new QGraphicsScene(this);
    setScene(scene);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    PenColor = Qt::white;
    // Загружаем PNG изображение
    image = QImage(1920, 1080, QImage::Format_RGBA8888);
    //image.fill(Qt::black);

    // Создаем QGraphicsPixmapItem на основе QImage и добавляем на сцену
    pixmapItem = scene->addPixmap(QPixmap::fromImage(image));

    // Устанавливаем начальную позицию (центр окна)
    initialPosition = pixmapItem->pos();
    scale(0.7, 0.7);
    scaleFactor *= 0.7;

    QRectF rect = pixmapItem->boundingRect();
    QColor myColor(9, 52, 83);
    rectItem = scene->addRect(rect, QPen(myColor, 5)); // Белая обводка толщиной 5 пикселей

    // Обновляем позицию рамки относительно pixmapItem
    rectItem->setPos(pixmapItem->pos());

    setCursor(Qt::ArrowCursor);
}

DrawingImage::~DrawingImage()
{
    // Чистим ресурсы
    delete scene;
}
QImage DrawingImage::GetImage()
{
    return image;
}

void DrawingImage::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        if (event->modifiers() & Qt::ControlModifier) {
            // Если Ctrl нажата, начинаем перетаскивание
            setCursor(Qt::SizeAllCursor);
            lastPoint = mapToScene(event->pos()).toPoint(); // Сохраняем начальную точку
            first = true;
        } else {
            // Начинаем рисовать
            drawing = true;
            lastPoint = mapToScene(event->pos()).toPoint(); // Запоминаем начальную точку рисования
        }
    }
}

void DrawingImage::mouseMoveEvent(QMouseEvent *event)
{
    QPointF currentPoint = mapToScene(event->pos()); // Текущая точка сцены

    if (drawing)
    {
        // Преобразуем координаты сцены в локальные координаты pixmapItem, чтобы учесть трансформацию
        QPointF localPoint = pixmapItem->mapFromScene(currentPoint);
        QPointF localLastPoint = pixmapItem->mapFromScene(lastPoint);

        // Рисуем на изображении в преобразованных координатах
        QPainter painter(&image);
        painter.setPen(QPen(PenColor, 5, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));

        // Рисуем линию от локальной последней точки к текущей локальной точке
        painter.drawLine(localLastPoint, localPoint);

        // Обновляем последнюю точку
        lastPoint = currentPoint;

        // Обновляем QGraphicsPixmapItem
        pixmapItem->setPixmap(QPixmap::fromImage(image));
    }
    else if (event->buttons() & Qt::LeftButton && (event->modifiers() & Qt::ControlModifier))
    {
        // Перемещаем изображение с учётом трансформации

        QPointF delta = currentPoint - lastPoint;
        pixmapItem->moveBy(delta.x(), delta.y());
        rectItem->moveBy(delta.x(), delta.y());

        // Обновляем последнюю точку
        lastPoint = currentPoint;
    }
}


void DrawingImage::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        if (event->modifiers() & Qt::ControlModifier) {
            // Если Ctrl была нажата, заканчиваем перетаскивание
            setCursor(Qt::ArrowCursor);
        } else {
            // Заканчиваем рисование
            drawing = false;
            first = true;
        }
    }
}


void DrawingImage::wheelEvent(QWheelEvent *event)
{
    // Масштабирование
    if (event->angleDelta().y() > 0) {
        scale(1.1, 1.1); // Увеличиваем масштаб
        scaleFactor *= 1.1;
    } else {
        scale(0.9, 0.9); // Уменьшаем масштаб
        scaleFactor *= 0.9;
    }
}



void DrawingImage::keyPressEvent(QKeyEvent *event)
{
    // Устанавливаем центр изображения как точку вращения
    pixmapItem->setTransformOriginPoint(pixmapItem->boundingRect().center());
    rectItem->setTransformOriginPoint(rectItem->boundingRect().center());

    // Вращение
    if (event->key() == Qt::Key_Left) {
        pixmapItem->setRotation(pixmapItem->rotation() - 10); // Вращаем на -10 градусов
        rectItem->setRotation(rectItem->rotation() - 10);
    } else if (event->key() == Qt::Key_Right) {
        pixmapItem->setRotation(pixmapItem->rotation() + 10); // Вращаем на 10 градусов
        rectItem->setRotation(rectItem->rotation() + 10);
    }
}

