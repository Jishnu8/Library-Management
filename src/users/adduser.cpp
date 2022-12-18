#include "include/users/adduser.h"
#include "ui_adduser.h"
#include <string>

using namespace std;

AddUser::AddUser(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddUser)
{
    ui->setupUi(this);
    ptrMessageBox = new MessageBox();
}

AddUser::~AddUser()
{
    delete ui;
    delete ptrMessageBox;
}

void AddUser::Show()
{
    this->show();
}

void AddUser::resetElements(){
    ui->txtFullName->clear();
    ui->txtUsername->clear();
    ui->txtPassword->clear();
    ui->txtPhoneNo->clear();
    ui->txtEmailId->clear();
    ui->txtAddress->clear();
    ui->txtComments->clear();
}

void AddUser::on_btnAdd_clicked()
{
    QSqlQuery query(MyDB::getInstance()->getDBInstance());
    query.clear();

    QString fullName = ui->txtFullName->text();
    QString username = ui->txtUsername->text();
    QString password = ui->txtPassword->text();
    QString phoneNo = ui->txtPhoneNo->text();
    QString emailId = ui->txtEmailId->text();
    QString address = ui->txtAddress->text();
    QString comments = ui->txtComments->text();

    query.prepare("insert into users (name, username, password, phone_no, email_id, address, comments) values ('" +fullName +"', '" +username +"', '" +password +"', '" +phoneNo +"', '" +emailId +"', '" +address +"', '" +comments +"')");
    if(!query.exec())
    {
        qDebug() << query.lastError().text() << query.lastQuery();
        ptrMessageBox->setText("Failed to Add User");
        ptrMessageBox->setTitle("Failed");
    }
    else
    {
        if(query.numRowsAffected() > 0)
        {
            qDebug() <<"read was successful "<< query.lastQuery();
            ptrMessageBox->setText("User Added Successfully");
            ptrMessageBox->setTitle("Success");
            resetElements();
        }
        else
            qDebug() <<"Unable to Add new User";
    }

    ptrMessageBox->Show();
}

void AddUser::on_btnReset_clicked()
{
    resetElements();
}

