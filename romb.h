#ifndef ROMB_H
#define ROMB_H
#include "square.h"

#include <QObject>
#include <QGraphicsItem>
#include "figure.h"

/* Наследуемся от класса Figure,
 * в котором реализован общий для всех фигур функционал
 * */
class Romb : public Figure
{
    Q_OBJECT

public:

    explicit Romb(QPointF point,QColor color,int LineWeight, QObject *parent = 0);
    ~Romb();

private:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QColor shapeColor;
    int LineWeight;

};

#endif // ROMB_H
