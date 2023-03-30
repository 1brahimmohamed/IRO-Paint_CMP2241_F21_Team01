#include <QJsonArray>
#include "src/utils/json_utilities.h"
#include "src/shapes/rectangle.h"
#include "src/shapes/circle.h"
#include "src/shapes/line.h"
#include "src/shapes/triangle.h"
#include "src/drawing/painttable.h"
#include "src/utils/commands.h"


/*
 * ----------------------Save Method----------------------
 * Take the path and the scene then save each figure in
 * the sene to a JSON File in a specific path
 * -------------------------------------------------------
 */
void json_utilities::save(PaintScene *scene, QString path)
{
    QVector<Figure*> *newVec = scene->SavedVec;

    // Making JSON File in a specific Path
    QFile saveFile(path);
    if (!saveFile.open(QIODevice::ReadWrite| QIODevice::Text)) {
            qWarning("Couldn't open save file.");
        }

    // Writing [ to open a list of maps in the file
    saveFile.write("[");

    // Looping on the vector to save it
    for(int i=0; i<newVec->size();i++){
        QVariantMap settings;

        // Getting the Vector start point, end point, color, line weight, and shape type
        QPointF point = newVec->at(i)->startPoint();
        QPointF point2 = newVec->at(i)->endPoint();
        QColor color = newVec->at(i)->shapeColor;
        QColor f_color = newVec->at(i)->fillColor;
        int LineW = newVec->at(i)->LineWeight;
        QString shapeName = newVec->at(i)->shapeTypeName;
        QString name = newVec->at(i)->name;


        // Setting the above values to the setting to path it the file
        settings[QString("Shape")] = QString("%1").arg(shapeName);
        settings[QString("FirstPoint")] = QString("%1, %2").arg(point.rx()).arg(point.ry());
        settings[QString("EndPoint")] = QString("%1, %2").arg(point2.rx()).arg(point2.ry());
        settings[QString("Color")] = QString("%1, %2, %3").arg(color.red()).arg(color.green()).arg(color.blue());
        settings[QString("fillColor")] = QString("%1, %2, %3").arg(f_color.red()).arg(f_color.green()).arg(f_color.blue());
        settings[QString("LineWeight")] = QString("%1").arg(LineW);
        settings[QString("ShapeName")] = QString("%1").arg(name);

        // Make a JSON Object and pass it to the file
        QJsonObject jsonobj = QJsonObject::fromVariantMap(settings);
        QJsonDocument json = QJsonDocument(jsonobj);

        saveFile.write(json.toJson());

        // Condition to avoid writing "," after the last element
        if(i<newVec->size()-1){
            saveFile.write(",");
        }
    }
    // Closing the List in the file
    saveFile.write("]");

    // Closing the file
    saveFile.close();
}

/*
 * ----------------------SavePNG Method----------------------
 * Take the path and save a PNG image in it
 * -------------------------------------------------------
 */
void json_utilities:: savePNG(PaintScene *scene, QString path){
     QFile saveFile(path);

     QPixmap pixMap = scene->view->grab(scene->sceneRect().toRect());
     pixMap.save(path);
}

/*
 * ----------------------open Method----------------------
 * Take the path and the scene then initialine each figure
 * of the JSON File in the scene
 * -------------------------------------------------------
 */

void json_utilities::open(PaintScene *scene,QTableWidget* table, QString path)
{
    // Opening the file of the path
    QFile jsonFile(path);
    QString json_string;

    if(jsonFile.open(QIODevice::ReadOnly | QIODevice::Text)){
            json_string = jsonFile.readAll();
            jsonFile.close();
    }

    auto json_doc = QJsonDocument::fromJson(json_string.toUtf8());
    QJsonArray jArr = json_doc.array();
    QJsonValue c_val, f_val, val2, val3, val4, val5, name_val;

    // Looping in the file shapes
    for(auto jsonObj : jArr)
    {
        // Getting the color Value as RGB
        QColor color;
        if(!jsonObj.toObject().value("Color").isUndefined()){
            c_val = jsonObj.toObject().value("Color");
            QString _color = c_val.toString();
            QStringList x = _color.split(", ");
            color.setRed(x[0].toInt());
            color.setGreen(x[1].toInt());
            color.setBlue(x[2].toInt());
        }else{
            color.setRed(0);
            color.setGreen(0);
            color.setBlue(0);
        }

        // Getting the Fill Color
        QColor fillColor;
        if(!jsonObj.toObject().value("fillColor").isUndefined()){
            f_val = jsonObj.toObject().value("fillColor");
            QString f_color = f_val.toString();
            QStringList _f = f_color.split(", ");
            fillColor.setRed(_f[0].toInt());
            fillColor.setGreen(_f[1].toInt());
            fillColor.setBlue(_f[2].toInt());
            qDebug() << fillColor;
        }
        else{
            fillColor.setRed(255);
            fillColor.setGreen(255);
            fillColor.setBlue(255);
        }

        // Getting The First Point as x, y values
        QPointF firstPoint;
        if(!jsonObj.toObject().value("FirstPoint").isUndefined()){
            val2 = jsonObj.toObject().value("FirstPoint");
            QString _FP = val2.toString();
            QStringList FP = _FP.split(", ");
            firstPoint.setX(FP[0].toInt());
            firstPoint.setY(FP[1].toInt());
        }else{
            continue;
        }

        // Getting The End Point as x, y values
        QPointF endPoint;
        if(!jsonObj.toObject().value("EndPoint").isUndefined()){
            val3 = jsonObj.toObject().value("EndPoint");
            QString _EP = val3.toString();
            QStringList EP = _EP.split(", ");
            endPoint.setX(EP[0].toInt());
            endPoint.setY(EP[1].toInt());
        }else{
            continue;
        }
        int LW;
        // Getting The Line Weigh Value
        if(!jsonObj.toObject().value("LineWeight").isUndefined()){
            val4 = jsonObj.toObject().value("LineWeight");
            QString _LW = val4.toString();
            LW = _LW.toInt();
        }else{
            LW = 1;
        }

        // Getting the shape Type
        QString _ST;
        if(!jsonObj.toObject().value("LineWeight").isUndefined()){
            val5 = jsonObj.toObject().value("Shape");
            _ST = val5.toString();
        }else{
            continue;
        }

        // Getting the shape name
        QString _SN;
        if(!jsonObj.toObject().value("ShapeName").isUndefined()){
            name_val = jsonObj.toObject().value("ShapeName");
            _SN = name_val.toString();
        }
        else{
            _SN = "Untitled";
        }

        // Conditions for each shape to initialize it

        if(_ST=="Rectangle"){
            Figure *item = new Rectangle(firstPoint,color,LW, fillColor);
            item->setPos(firstPoint);
            item->setEndPoint(endPoint,false);
            item->name = _SN;
            QUndoCommand *addCommand = new AddCommand(scene,item,firstPoint,table);
            scene->undoStack->push(addCommand);}

        else if(_ST=="Circle"){
            Figure *item = new Circle(firstPoint,color,LW,fillColor);
            item->setPos(firstPoint);
            item->setEndPoint(endPoint,false);
            item->name = _SN;
            QUndoCommand *addCommand = new AddCommand(scene,item,firstPoint,table);
            scene->undoStack->push(addCommand);
        }
        else if(_ST=="Line"){
            Figure *item = new Line(firstPoint,color,LW);
            item->setPos(firstPoint);
            item->setEndPoint(endPoint,false);
            item->name = _SN;
            QUndoCommand *addCommand = new AddCommand(scene,item,firstPoint,table);
            scene->undoStack->push(addCommand);
        }
        else if(_ST=="Triangle"){
            Figure *item = new Triangle(firstPoint,color,LW, fillColor);
            item->setPos(firstPoint);
            item->setEndPoint(endPoint,false);
            item->name = _SN;
            QUndoCommand *addCommand = new AddCommand(scene,item,firstPoint,table);
            scene->undoStack->push(addCommand);
        }
    }
    PaintTable::UpdateTable(table,*scene->ItemsVec);
}
