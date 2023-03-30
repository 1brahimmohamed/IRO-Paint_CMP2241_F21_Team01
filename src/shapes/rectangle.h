#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <QObject>
#include <QGraphicsItem>
#include "src/shapes/figure.h"


class Rectangle : public Figure
{
    Q_OBJECT

public:
    explicit Rectangle(QPointF point,QColor color,int LineWeightbool, QColor fillColor, QObject *parent = 0);
    ~Rectangle();

private:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    float sideLen1,
          sideLen2;
};

#endif // RECTANGLE_H
