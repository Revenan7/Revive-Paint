#ifndef DRAWINGIMAGE_H
#define DRAWINGIMAGE_H

#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QImage>
#include <QPoint>
#include <QLabel>


class DrawingImage : public QGraphicsView
{
    Q_OBJECT

public:
    explicit DrawingImage(QWidget *parent = nullptr);
    ~DrawingImage();
    QImage GetImage();
    QColor PenColor;

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void wheelEvent(QWheelEvent* event) override;
    void keyPressEvent(QKeyEvent *event) override;

    // void dragEnterEvent(QDragEnterEvent *event) override;
    // void dragMoveEvent(QDragMoveEvent *event) override;
    // void dropEvent(QDropEvent *event) override;


private:
    QGraphicsScene *scene;
    QGraphicsPixmapItem *pixmapItem;
    QImage image;
    bool drawing;
    QPointF lastPoint;
    QPointF lastPointDraw;
    qreal scaleFactor;
    qreal savedScaleFactor;
    qreal savedSavelFactor;
    QPointF pixmapStartPos;
    QPointF lastPos;
    QPointF initialPosition;
    QPointF deltaFromWindowCenter;
    bool first;
    QGraphicsRectItem *rectItem;


};

#endif // DRAWINGIMAGE_H
