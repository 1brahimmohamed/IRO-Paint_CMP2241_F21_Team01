#ifndef JSON_UTILITIES_H
#define JSON_UTILITIES_H

#include <QJsonObject>
#include <QString>
#include <QFile>
#include <QFileDialog>
#include <QPointF>
#include <QJsonDocument>
#include <QJsonObject>

#include "src/drawing/paintscene.h"
#include "src/shapes/figure.h"

class json_utilities
{
public:
    json_utilities();
    static void save(PaintScene *scene, QString path);
    static void open(PaintScene *scene,QTableWidget* table, QString path);
    static void savePNG(PaintScene *scene, QString path);


private:
    PaintScene *myGraphicsScene;
};
#endif // JSON_UTILITIES_H
