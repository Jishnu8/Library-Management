#include "include/dialog_box/messagebox.h"
#include "ui_messagebox.h"

MessageBox::MessageBox(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MessageBox)
{
    ui->setupUi(this);
}

MessageBox::~MessageBox()
{
    delete ui;
}

void MessageBox::Show(){
    ui->img->setStyleSheet("background-image: url(:/inf.jpg);");
    this->show();
}

void MessageBox::on_okButton_clicked()
{
    this->close();
}

void MessageBox::setText(QString msg){
    ui->text->setText(msg);
}

void MessageBox::setTitle(QString msg){
    ui->title->setText(msg);
}

