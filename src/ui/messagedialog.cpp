#include "src/ui/messagedialog.h"
#include "ui_messagedialog.h"
#include "src/utils/json_utilities.h"
#include <QFileDialog>


messageDialog::messageDialog(QString message,QString LeftText,QString RightText,QWidget *parent) :
    QDialog(parent, Qt::FramelessWindowHint | Qt::WindowSystemMenuHint),
    ui(new Ui::messageDialog)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_TranslucentBackground);

    QString yesBtnStyleSheet="QPushButton {"
                   "background-color: #f9f9f9;"
                   "color: black;"
                   "font: 11pt Montserrat;"
                   "border-radius: 20px;"
                   "}"
                   "QPushButton:hover{"
                   "background-color: #e0e0e0;"
                   "}"
                   "QPushButton:pressed{"
                   "background-color: #06ff7b;"
                   "}";

    QString noBtnStyleSheet="QPushButton {"
                   "background-color: #f9f9f9;"
                   "color: black;"
                   "font: 11pt Montserrat;"
                   "border-radius: 20px;"
                   "}"
                   "QPushButton:hover{"
                   "background-color: #e0e0e0;"
                   "}"
                   "QPushButton:pressed{"
                   "background-color: #fd2873;"
                   "}";

    ui->yesBtn->setStyleSheet(yesBtnStyleSheet);
    ui->noBtn->setStyleSheet(noBtnStyleSheet);

    ui->message->setText(message);
    ui->yesBtn->setText(LeftText);
    ui->noBtn->setText(RightText);
    this->setModal(true);
}

messageDialog::~messageDialog()
{
    delete ui;
}

void messageDialog::on_yesBtn_clicked()
{
    accept();
}


void messageDialog::on_closeBtn_clicked()
{
    closed=true;
    reject();
}


void messageDialog::on_noBtn_clicked()
{
    reject();
}

void messageDialog::mouseMoveEvent(QMouseEvent *event)
{
    if( event->buttons().testFlag(Qt::LeftButton) && mMoving){
        this->move(this->pos() + (event->pos() - mLastMousePosition));
    }
}

void messageDialog::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton){
        mMoving = true;
        mLastMousePosition = event->pos();
    }
}

void messageDialog::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton){
        mMoving = false;
    }
}

void messageDialog::closeEvent(QCloseEvent *event)
{
    on_closeBtn_clicked();
    Q_UNUSED(event)
}


