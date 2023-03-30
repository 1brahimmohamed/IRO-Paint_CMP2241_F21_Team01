#include "src/shapes/figure.h"
#include <QPainter>


// Initializing the shapes counters to 1
int Figure::rCount = 1;
int Figure::cCount = 1;
int Figure::lCount = 1;
int Figure::tCount = 1;

/*
 * Figure Constructor that initialize the Start and End points.
 */

Figure::Figure(QPointF point, QObject *parent) :
    QObject(parent), QGraphicsItem()
{
    this->setStartPoint(mapFromScene(point));
    this->setEndPoint(mapFromScene(point));
    setFlag(QGraphicsItem::ItemIsSelectable);
    connect(this, &Figure::pointChanged, this, &Figure::updateCircle);
}

Figure::~Figure()
{

}

QRectF Figure::boundingRect() const
{

    return QRectF((endPoint().x() > startPoint().x() ? startPoint().x() : endPoint().x()) - 5,
                  (endPoint().y() > startPoint().y() ? startPoint().y() : endPoint().y()) - 5,
                  qAbs(endPoint().x() - startPoint().x()) + 10,
                  qAbs(endPoint().y() - startPoint().y()) + 10);
}

void Figure::updateCircle()
{
    this->update((endPoint().x() > startPoint().x() ? startPoint().x() : endPoint().x()) - 5,
                 (endPoint().y() > startPoint().y() ? startPoint().y() : endPoint().y()) - 5,
                 qAbs(endPoint().x() - startPoint().x()) + 10,
                 qAbs(endPoint().y() - startPoint().y()) + 10);
}

/*
 * -------------------------------------------
 * Setters and Getters
 * -------------------------------------------
 */

/*
 * start point setter
 */
void Figure::setStartPoint(const QPointF point)
{
    m_startPoint = mapFromScene(point);
    emit pointChanged();
}

/*
 * end point setter
 */
void Figure::setEndPoint(const QPointF point, bool test)
{
    if(test){
    m_endPoint = mapFromScene(point);
    emit pointChanged();}
    else{
        m_endPoint = point;
        emit pointChanged();
    }
}

/*
 * start point getter
 */
QPointF Figure::startPoint() const
{
    return m_startPoint;
}

/*
 * end point getter
 */
QPointF Figure::endPoint() const
{
    return m_endPoint;
}
void Figure :: countZero(){
    lCount= rCount=cCount=tCount=1;
}
