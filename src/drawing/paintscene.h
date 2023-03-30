#ifndef PAINTSCENE_H
#define PAINTSCENE_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QUndoStack>
#include <QGraphicsView>
#include <QTableWidget>

#include "src/shapes/figure.h"




class PaintScene : public QGraphicsScene
{
    Q_OBJECT
    Q_PROPERTY(int typeFigure
               READ typeFigure WRITE setTypeFigure
               NOTIFY typeFigureChanged)

public:
    QGraphicsView* view;
    QPointF startPoint;
    QPointF EndPoint;
    QVector<Figure*> *ItemsVec;
    QVector<Figure*> *SavedVec;
    QTableWidget* table;
    QUndoStack *undoStack;
    explicit PaintScene(QGraphicsView *view,QTableWidget* table, QObject *parent = 0);
    ~PaintScene();
    QString defaultPath = "";

    void setFillColor(QColor color);
    int typeFigure() const;
    void setTypeFigure(const int type);
    bool Modified = false;

    enum FigureTypes {
        RectangleType,
        CircleType,
        TriangleType,
        LineType,
        EraserType
    };
    void setColor(QColor color);
    void setWeight(int Value);

signals:
    void typeFigureChanged();

private:
    Figure *tempFigure;


private:
    void mousePressEvent(QGraphicsSceneMouseEvent * event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    QColor paintingColor;
    int LineWeight;
    int m_typeFigure;
    bool selectingItem;
    QColor fillColor = Qt::white;

};

#endif // PAINTSCENE_H
