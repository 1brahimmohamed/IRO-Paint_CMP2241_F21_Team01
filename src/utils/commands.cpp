#include <QGraphicsScene>
#include "src/utils/commands.h"
#include "src/drawing/painttable.h"



AddCommand::AddCommand(PaintScene *scene,Figure* item, QPointF LastPoint,QTableWidget* table,QUndoCommand *parent)
    : QUndoCommand(parent)
{
    static int itemCount = 0;

    myGraphicsScene = scene;
    myDiagramItem = item;
    scene->update();
    ++itemCount;
    this->table= table;
    WasModified= scene->Modified;
    IsFirstTime=true;
    Q_UNUSED(LastPoint)

}

AddCommand::~AddCommand()
{
    if (!myDiagramItem->scene())
        myDiagramItem->hide();
}

void AddCommand::undo()
{

    myGraphicsScene->removeItem(myDiagramItem);
    // remove figure from the vector
    myGraphicsScene->ItemsVec->pop_back();
    myGraphicsScene->SavedVec->pop_back();
    myGraphicsScene->update();
    PaintTable::UpdateTable(table, *myGraphicsScene->ItemsVec);
    WillModify=myGraphicsScene->Modified;
    myGraphicsScene->Modified=WasModified;
}

void AddCommand::redo()
{   myGraphicsScene->ItemsVec->push_back(myDiagramItem);
    myGraphicsScene->SavedVec->push_back(myDiagramItem);
    myGraphicsScene->addItem(myDiagramItem);
    myDiagramItem->setPos(initialPosition);
    myGraphicsScene->clearSelection();
    myGraphicsScene->update();
    PaintTable::UpdateTable(table, *myGraphicsScene->ItemsVec);
    if(IsFirstTime){
    myGraphicsScene->Modified=true;
    IsFirstTime=false;
    }
    else{
        myGraphicsScene->Modified=WillModify;
    }
}

DeleteCommand::DeleteCommand(PaintScene *scene,Figure* item, QPointF LastPoint,QTableWidget* table,QUndoCommand *parent)
    : QUndoCommand(parent)
{
    static int itemCount = 0;

    myGraphicsScene = scene;
    myDiagramItem = item;
    this->table= table;
    scene->update();
    ++itemCount;
    WasModified= scene->Modified;
    IsFirstTime=true;
    Q_UNUSED(LastPoint)


}

DeleteCommand::~DeleteCommand()
{
    if (!myDiagramItem->scene())
        myDiagramItem->hide();
}

void DeleteCommand::undo()
{
        myGraphicsScene->ItemsVec->push_back(myDiagramItem);
        myGraphicsScene->SavedVec->insert(ItemIndex, myDiagramItem);
        myGraphicsScene->addItem(myDiagramItem);
        myDiagramItem->setPos(initialPosition);
        myGraphicsScene->clearSelection();
        myGraphicsScene->update();
        PaintTable::UpdateTable(table, *myGraphicsScene->ItemsVec);
        WillModify=myGraphicsScene->Modified;
        myGraphicsScene->Modified=WasModified;
}

void DeleteCommand::redo()
{
    myGraphicsScene->removeItem(myDiagramItem);
    // remove figure from the vector
    myGraphicsScene->ItemsVec->remove(myGraphicsScene->ItemsVec->indexOf(myDiagramItem));
    ItemIndex=myGraphicsScene->SavedVec->indexOf(myDiagramItem);
    myGraphicsScene->SavedVec->remove(ItemIndex);
    myGraphicsScene->update();
    PaintTable::UpdateTable(table, *myGraphicsScene->ItemsVec);
    if(IsFirstTime){
    myGraphicsScene->Modified=true;
    IsFirstTime=false;
    }
    else{
        myGraphicsScene->Modified=WillModify;
    }

}


void ButtonsCommand::clearScene(PaintScene *scene)
{
    delete scene->ItemsVec;
    delete scene->undoStack;
    scene->clear();
    scene->undoStack =new QUndoStack();
    scene->ItemsVec = new QVector<Figure*>();
    scene->SavedVec = new QVector<Figure*>();
}
