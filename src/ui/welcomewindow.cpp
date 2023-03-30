#include "src/ui/welcomewindow.h"
#include "ui_welcomewindow.h"
#include <QFileDialog>


WelcomeWindow::WelcomeWindow(QWidget *parent) :
    QMainWindow(parent, Qt::FramelessWindowHint | Qt::WindowSystemMenuHint),
    ui(new Ui::WelcomeWindow)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_TranslucentBackground);
    QString cs1="QPushButton {"
                   "background-color: black;"
                   "color: white;"
                   "border-radius: 13px;"
                   "}"
                   "QPushButton:hover {"
                     "color:#fd369e ;"
                   "}"
                   "QPushButton:pressed {"
                   "color:red ;"
                   "}";
    ui->newPaintBtn->setStyleSheet(cs1);
    ui->openPaintBtn->setStyleSheet(cs1);
}

WelcomeWindow::~WelcomeWindow()
{
    delete ui;
}

/*
 * --------------------New button----------------------
 * Once clicked, it initialize a new window (Paint Window)
 * and open it, then hide the current
 */
void WelcomeWindow::on_newPaintBtn_clicked()
{
    p->show();
    this->hide();
}

/*
 * --------------------Open button--------------------
 * Opening Dialog and getting the path from it
 * Then pass the path to (open function) in the scene.
 */
void WelcomeWindow::on_openPaintBtn_clicked()
{
    QString path = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                    QDir::homePath() + "/Documents/IRO Arts",
                                                    tr("JSON (*.json)"));
    if (!path.isNull()){
    p->show();
    this->hide();
    p->open(path);
}
}

