#ifndef PAINTTABLE_H
#define PAINTTABLE_H

#include <QTableWidget>
#include <QVector>

#include "src/shapes/figure.h"


class PaintTable
{
public:
    PaintTable();
    static void UpdateTable(QTableWidget* table, QVector<Figure*> ItemVec);
    static void UpdateInfoTable(QTableWidget*table, Figure* item);
    static void SortDVec(QVector<Figure*>* ItemVec);
    static void SortAVec(QVector<Figure*>* ItemVec);
    static void ClearInfoTable(QTableWidget* table);




private:
    static bool compareAs(const Figure* first, const Figure* second);
    static bool compareDs(const Figure* first, const Figure* second);
};

#endif // PAINTTABLE_H
