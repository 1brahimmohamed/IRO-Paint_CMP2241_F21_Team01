#include "src/drawing/painttable.h"

PaintTable::PaintTable()
{

}


void PaintTable::UpdateTable(QTableWidget *table, QVector<Figure *> ItemVec)
{
    QStringList TableLabel;
    //table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    TableLabel<<"Name"<<"Type"<<"Perimter"<<"Color"<<"LineWeight";

    table->setColumnCount(3);
    table->setHorizontalHeaderLabels(TableLabel);
    while (table->rowCount() > 0)
    {
        table->removeRow(0);
    }
    int rowcount=0;
    for(auto* item:ItemVec){
        // Initializing the Figure Values
        QString name= item->name;
        QString Type= item->shapeTypeName;
        QString Perimeter= QString::number(item->perimeter);

        // Insert New row in the table
        table->insertRow(table->rowCount());

        // Setting the row values
        table->setItem(table->rowCount()-1, 0, new QTableWidgetItem(name));
        table->setItem(table->rowCount()-1, 1, new QTableWidgetItem(Type));
        table->setItem(table->rowCount()-1, 2, new QTableWidgetItem(Perimeter));      
        table->item(rowcount,2)->setFlags(table->item(rowcount,2)->flags() &= ~Qt::ItemIsEditable);
        table->item(rowcount,1)->setFlags(table->item(rowcount,1)->flags() &= ~Qt::ItemIsEditable);
        rowcount++;
    }

}

void PaintTable::UpdateInfoTable(QTableWidget *table, Figure *item)
{
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    table->setRowCount(8);
    table->setColumnCount(1);
    table->setColumnWidth(0,300);
    QStringList Vlist,Hlist;
    Vlist<<"name"<<"type"<<"Perimeter"<<"Borders Color"<<"Fill Color"<<"StartPoint"<<"EndPoint"<<"LineWeight";
    Hlist<<"Value";
    table->setVerticalHeaderLabels(Vlist);
    table->setHorizontalHeaderLabels(Hlist);
    table->setItem(0, 0, new QTableWidgetItem(item->name));
    table->setItem(1, 0, new QTableWidgetItem(item->shapeTypeName));
    table->setItem(2, 0, new QTableWidgetItem(QString::number(item->perimeter)));
    table->setItem(3, 0, new QTableWidgetItem(item->shapeColor.name(QColor::HexRgb)));
    if(item->fillColor == Qt::white){
        table->setItem(4, 0, new QTableWidgetItem("NO Fill"));
    }else{
        table->setItem(4, 0, new QTableWidgetItem(item->fillColor.name(QColor::HexRgb)));
    }
    table->setItem(5, 0, new QTableWidgetItem(QString("%1, %2").arg(item->startPoint().rx()).arg(item->startPoint().ry())));
    table->setItem(6, 0, new QTableWidgetItem(QString("%1, %2").arg(item->endPoint().rx()).arg(item->endPoint().ry())));
    table->setItem(7, 0, new QTableWidgetItem(QString::number(item->LineWeight)));
}

/*
 * Table Buttons
 */
void PaintTable::SortDVec(QVector<Figure *> *ItemVec)
{
    std::sort(ItemVec->begin(), ItemVec->end(), compareDs);
}

void PaintTable::SortAVec(QVector<Figure *> *ItemVec)
{
    std::sort(ItemVec->begin(), ItemVec->end(), compareAs);
}

void PaintTable::ClearInfoTable(QTableWidget *table)
{
    while (table->rowCount() > 0)
    {
        table->removeRow(0);
    }
}

/*
 * Function for the above buttons
 */
bool PaintTable::compareAs(const Figure *first, const Figure *second)
{
    return first->perimeter < second->perimeter;
}

bool PaintTable::compareDs(const Figure *first, const Figure *second)
{
    return first->perimeter > second->perimeter;
}


