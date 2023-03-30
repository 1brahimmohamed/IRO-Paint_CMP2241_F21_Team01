#ifndef PAINTWINDOW_H
#define PAINTWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QResizeEvent>

#include "src/drawing/paintscene.h"
#include "src/ui/messagedialog.h"


namespace Ui {
class PaintWindow;
}

class PaintWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit PaintWindow(QWidget *parent = nullptr);
    ~PaintWindow();
    PaintScene *scene;
    QTimer *timer;
    void open(QString path);
    void on_menuSave(QString path);


private slots:
    void slotTimer();
    void on_triangleBtn_clicked();

    void on_rectangleBtn_clicked();

    void on_lineBtn_clicked();

    void on_circleBtn_clicked();

    void on_undoBtn_clicked();

    void on_redoBtn_clicked();

    void on_colorBtn_clicked();

    void on_saveBtn_clicked();

    void on_verticalSlider_sliderMoved(int position);

    void on_tableBtn_clicked();

    void on_ersr_Btn_clicked();

    void on_searchBar_returnPressed();


    void on_DataTable_cellChanged(int row, int column);

    void on_SortASBtn_clicked();

    void on_SortDSBtn_clicked();




    void on_DataTable_cellClicked(int row, int column);
    void on_logoBtn_clicked();

    void on_menuNew_clicked();

    void on_menuOpen_clicked();

    void on_menuSave_clicked();




    void on_infoBtn_clicked();

    void on_borderCBtn_clicked();

protected:
    void mouseMoveEvent(QMouseEvent* event);
    void mousePressEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
private:
    Ui::PaintWindow *ui;
    QPoint mLastMousePosition;
    bool mMoving;
    void closeEvent(QCloseEvent *event);
    bool isFilled=true;
    QColor fillColor=Qt::black;
    QVector<QString> dialogMessage;
};

#endif // PAINTWINDOW_H
