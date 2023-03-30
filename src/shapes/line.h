#ifndef LINE_H
#define LINE_H

#include <QObject>
#include <QGraphicsItem>
#include "src/shapes/figure.h"



class Line : public Figure
{
    Q_OBJECT

public:
    explicit Line(QPointF point,QColor color,int LineWeight, QObject *parent = 0);
    ~Line();

private:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};


#endif // LINE_H
