#ifndef CIRCLE_H
#define CIRCLE_H

#include <QObject>
#include <QGraphicsItem>
#include "src/shapes/figure.h"


class Circle : public Figure
{
    Q_OBJECT

public:

    explicit Circle(QPointF point,QColor color,int LineWeight, QColor fillColor, QObject *parent = 0);
    ~Circle();

private:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

};

#endif // CIRCLE_H
