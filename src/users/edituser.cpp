#include "include/users/edituser.h"
#include "ui_edituser.h"
#include <string>

using namespace std;

EditUser::EditUser(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditUser)
{
    ui->setupUi(this);
    id = "1";
    ptrMessageBox = new MessageBox();
}

EditUser::~EditUser()
{
    delete ui;
    delete ptrMessageBox;
}

void EditUser::Show()
{
    this->show();
}

void EditUser::resetElements(){
    ui->txtFullName->setText(allItems[0]);
    ui->txtUsername->setText(allItems[1]);
    ui->txtPassword->setText(allItems[2]);
    ui->txtPhoneNo->setText(allItems[3]);
    ui->txtEmailId->setText(allItems[4]);
    ui->txtAddress->setText(allItems[5]);
    ui->txtComments->setText(allItems[6]);
}

void EditUser::setLineEditText(QString fullName, QString username, QString password,
                               QString phoneNo, QString emailId, QString address,
                               QString comments){
    ui->txtFullName->setText(fullName);
    ui->txtUsername->setText(username);
    ui->txtPassword->setText(password);
    ui->txtPhoneNo->setText(phoneNo);
    ui->txtEmailId->setText(emailId);
    ui->txtComments->setText(comments);
    ui->txtAddress->setText(address);

    allItems = new QString[7];
    allItems[0] = fullName; allItems[1] = username; allItems[2] = password; allItems[3] = phoneNo; allItems[4] = emailId;
    allItems[5] = address; allItems[6] = comments;
}

void EditUser::on_btnReset_clicked()
{
    resetElements();
}


void EditUser::on_btnEdit_clicked()
{
    QSqlQuery query(MyDB::getInstance()->getDBInstance());
    query.clear();

    QString fullName = ui->txtFullName->text();
    QString username = ui->txtUsername->text();
    QString password = ui->txtPassword->text();
    QString phoneNo = ui->txtPhoneNo->text();
    QString emailId = ui->txtEmailId->text();
    QString comments = ui->txtComments->text();
    QString address = ui->txtAddress->text();

    query.prepare("update users set name='" +  fullName + "', username='" + username + "', password='" + password + "', phone_no='" + phoneNo + "', email_id='" + emailId + "', address='" + address + "', comments='" + comments + "' where access_no = '" + id + "'");
    if(!query.exec())
    {
        qDebug() << query.lastError().text() << query.lastQuery();
        ptrMessageBox->setText("Failed to Edit User");
        ptrMessageBox->setTitle("Failed");
        ptrMessageBox->Show();
    }
    else
    {
        if(query.numRowsAffected() > 0)
        {
            qDebug() <<"read was successful "<< query.lastQuery();
            ptrMessageBox->setText("User Edited Successfully");
            ptrMessageBox->setTitle("Success");
            resetElements();
            ptrMessageBox->Show();
            this->close();
        }
        else
            qDebug() <<"Unable to Edit new User";
    }
}

