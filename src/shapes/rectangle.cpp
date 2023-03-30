#include "src/shapes/rectangle.h"
#include <QPainter>
#include <QUndoCommand>
#include "src/utils/commands.h"


Rectangle::Rectangle(QPointF point,QColor color,int LineWeight, QColor fillColor, QObject *parent) :
    Figure(point,parent)
{
    /*
     *  Setting the color and Line weight and then make the name
     *  Accoding to a counter to the class shapes (rCount)
     */
    Q_UNUSED(point)
    shapeColor=color;
    this->LineWeight=LineWeight;
    this->name=QString("Rectangle %1").arg(rCount);

    this->fillColor = fillColor;
    rCount++;
}



Rectangle::~Rectangle()
{

}

void Rectangle::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(QPen(shapeColor, LineWeight));
    if(fillColor != Qt::white){
        painter->setBrush(Qt::SolidPattern);
        painter->setBrush(fillColor);
    }
    else{
        painter->setBrush(Qt::NoBrush);
    }


    shapeTypeName = "Rectangle";


    QRectF rect(endPoint().x() > startPoint().x() ? startPoint().x() : endPoint().x(),
                endPoint().y() > startPoint().y() ? startPoint().y() : endPoint().y(),
                qAbs(endPoint().x() - startPoint().x()),
                qAbs(endPoint().y() - startPoint().y()));
    QLineF line1(rect.bottomLeft().x(),rect.bottomLeft().y(),rect.bottomRight().x(),rect.bottomRight().y());
    this->sideLen1= line1.length();
    QLineF line2(rect.bottomLeft().x(),rect.bottomLeft().y(),rect.topLeft().x(),rect.topLeft().y());
    this->sideLen2= line2.length();
    this-> perimeter=(sideLen1+sideLen2)*2;



    painter->drawRect(rect);

    Q_UNUSED(option)
    Q_UNUSED(widget)
}

