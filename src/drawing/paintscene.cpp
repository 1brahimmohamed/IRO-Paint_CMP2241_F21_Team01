#include "src/drawing/paintscene.h"
#include "src/shapes/circle.h"
#include "src/shapes/triangle.h"
#include "src/shapes/rectangle.h"
#include "src/shapes/line.h"
#include "src/utils/commands.h"
#include <QVector>



PaintScene::PaintScene(QGraphicsView *view,QTableWidget* table, QObject *parent) : QGraphicsScene(parent)
{
    this->view = view;
    // Initializing Undo Stack for Undo and Redo functions
    undoStack = new QUndoStack(this);

    // Initializing the shapes color with black
    paintingColor = Qt::black;

    // Initializing the Line weigh of the shapes with 1
    LineWeight = 1;

    // Initialize filling status

    // Initializing vector to contain the shapes info
    ItemsVec = new QVector<Figure*>();
    SavedVec = new QVector<Figure*>();
    selectingItem=false;
    this->table = table;
}

/*
 * Empty Constructor for PaingScene
 */
PaintScene::~PaintScene()
{
}

void PaintScene::setFillColor(QColor color)
{
    fillColor =color;
}

/*
 * -------------------typeFigure------------------
 * Function that return an integer that related to
 * the selected button from the shapes menu.
 * -----------------------------------------------
 */
int PaintScene::typeFigure() const
{
    return m_typeFigure;
}

/*
 * -----------------setTypeFigure-----------------
 * Function that update the type when we select
 * another button from the shapes menu
 * -----------------------------------------------
 */
void PaintScene::setTypeFigure(const int type)
{
    m_typeFigure = type;
}

/*
 * -----------------setColor-----------------
 * Function that update the color when we select
 * another color from the color bar.
 * -----------------------------------------------
 */
void PaintScene::setColor(QColor color)
{
    paintingColor=color;
}

/*
 * -----------------setWeight-----------------
 * Function that update the weight when we select
 * another weight from the weight bar.
 * -----------------------------------------------
 */
void PaintScene::setWeight(int Value)
{
    LineWeight=Value;
}



/*
 * ------------------ mousePressEvent Function --------------------
 * Function to initialize the first point of a specific shape in
 * the graphic view. The Shape is know from the typeFigure method
 * above, and it selected with switch case.
 * ----------------------------------------------------------------
 */
void PaintScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{

    switch (m_typeFigure) {
    case RectangleType: {
        // Getting the start point from the mouse event
        startPoint = event->scenePos();

        // Make an object from the rectangle class to draw the shape
        Rectangle *item = new Rectangle(startPoint,paintingColor,LineWeight,fillColor);

        // Getting the end point and pass it the the above object
        EndPoint = event->pos();
        item->setPos(EndPoint);

        // Set the above object to the tempFigure to use it later
        tempFigure = item;
        this->addItem(tempFigure);
        break;
    }
    case CircleType: {
      // Getting the start point from the mouse event
      startPoint = event->scenePos();

      // Make an object from the circle class to draw the shape
      Circle *item = new Circle(startPoint,paintingColor,LineWeight,fillColor);

      // Getting the end point and pass it the the above object
      EndPoint = event->pos();
      item->setPos(event->pos());

      // Set the above object to the tempFigure to use it later
      tempFigure = item;
      this->addItem(tempFigure);
      break;

    }
    case LineType: {
      // Getting the start point from the mouse event
      startPoint = event->scenePos();

      // Make an object from the Line class to draw the shape
      Line *item = new Line(startPoint,paintingColor,LineWeight);

      // Getting the end point and pass it the the above object
      EndPoint = event->pos();
      item->setPos(event->pos());

      // Set the above object to the tempFigure to use it later
      tempFigure = item;
      this->addItem(tempFigure);
      break;

    }
    case TriangleType: {
        // Getting the start point from the mouse event
        startPoint = event->scenePos();

        // Make an object from the Triangle class to draw the shape
        Figure *item = new Triangle(startPoint, paintingColor, LineWeight,fillColor);
        item->setPos(event->pos());

        // Set the above object to the tempFigure to use it later
        tempFigure = item;
        this->addItem(tempFigure);
        break;
    }

    /*
     * In case for when you're selecting the eraser button and clicked on something
     */

    case EraserType :{

        // Getting the position of the mouse.
        QPointF mousePos(event->buttonDownScenePos(Qt::LeftButton).x(),
                             event->buttonDownScenePos(Qt::LeftButton).y());

        // Getting the items at this position and puts them in the list.
        QVector<QGraphicsItem *> deletedItems = items(mousePos);

        //then, Deleting the item from the view and update.
        if(!deletedItems.isEmpty()){
            tempFigure= (Figure*)deletedItems[0];
            selectingItem = true;
        }
        break;
    }
    /*
     * By Default, The Rectangle button is pressed.
     */
    default:{
        Rectangle *item = new Rectangle(event->scenePos(),paintingColor,LineWeight,fillColor);
        item->setPos(event->pos());
        tempFigure = item;
        this->addItem(tempFigure);
        break;
    }
    }
}


/*
 * ------------------ mouseMoveEvent Function ------------------
 * The function is updating the end point while we move with the
 * mouse, untill we release it.
 */
void PaintScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if(m_typeFigure!=EraserType){
        EndPoint = event->scenePos();
        tempFigure-> setEndPoint(EndPoint);
        this->update(QRectF(0,0,this->width(), this->height()));}
}

/*
 * ------------------ mouseReleaseEvent Function ------------------
 * Function to get the end point of the shape and set it to the
 * tempObject that selected above in the mousePressEvent
 * ----------------------------------------------------------------
 */
void PaintScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if(m_typeFigure!=EraserType){
        EndPoint = event->scenePos();
        tempFigure->setEndPoint(EndPoint);
        this->update();
        QUndoCommand *addCommand = new AddCommand(this,tempFigure,startPoint,table);
        undoStack->push(addCommand);
    }
    else{
        if(selectingItem){
            //we add the command for the deletion to the undo stack.
            QUndoCommand *deleteCommand = new DeleteCommand(this,tempFigure,startPoint,table);
            undoStack->push(deleteCommand);
            selectingItem=false;
        }
    }
}


