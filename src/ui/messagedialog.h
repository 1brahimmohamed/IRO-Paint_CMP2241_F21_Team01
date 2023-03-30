#ifndef MESSAGEDIALOG_H
#define MESSAGEDIALOG_H

#include <QDialog>
#include <QMouseEvent>
#include "src/ui/paintwindow.h"


namespace Ui {
class messageDialog;
}

class messageDialog : public QDialog
{
    Q_OBJECT

public:
    explicit messageDialog(QString message,QString LeftText,QString RightText,QWidget *parent = nullptr);
    ~messageDialog();
    int actionType;
    bool exitCheck = true;
    int dialogCheck;
    bool closed=false;


private slots:
    void on_yesBtn_clicked();

    void on_closeBtn_clicked();

    void on_noBtn_clicked();



protected:
    void mouseMoveEvent(QMouseEvent* event);
    void mousePressEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
private:
    Ui::messageDialog *ui;
    void closeEvent(QCloseEvent *event);
    QPoint mLastMousePosition;
    bool mMoving;
};

#endif // MESSAGEDIALOG_H
