#include "src/ui/about.h"
#include "ui_about.h"


about::about(QWidget *parent) :
    QDialog(parent, Qt::FramelessWindowHint | Qt::WindowSystemMenuHint),
    ui(new Ui::about)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_TranslucentBackground);
}

about::~about()
{
    delete ui;
}

void about::on_closeBtn_clicked()
{
    this->hide();
}




