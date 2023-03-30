#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <QObject>
#include <QGraphicsItem>
#include "src/shapes/figure.h"


class Triangle : public Figure
{
    Q_OBJECT

public:
    explicit Triangle(QPointF point,QColor color,int LineWeight, QColor fillColor, QObject *parent = 0);

    ~Triangle();

private:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    float side1,side2,side3;
};

#endif // TRIANGLE_H
