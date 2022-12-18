#include "include/dialog_box/criticalmsgbox.h"
#include "ui_criticalmsgbox.h"

CriticalMsgBox::CriticalMsgBox(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CriticalMsgBox)
{
    ui->setupUi(this);
    execute = false;
    waiting = true;
}

CriticalMsgBox::~CriticalMsgBox()
{
    delete ui;
}

void CriticalMsgBox::Show(){
    ui->img->setStyleSheet("background-image: url(:/critical.jpg);");
    this->show();
}

void CriticalMsgBox::on_cancelButton_clicked()
{
    execute = false;
    waiting = false;
    this->close();
}


void CriticalMsgBox::on_okButton_clicked()
{
    execute = true;
    waiting = false;
    this->close();
}

void CriticalMsgBox::setText(QString msg){
    ui->text->setText(msg);
}
