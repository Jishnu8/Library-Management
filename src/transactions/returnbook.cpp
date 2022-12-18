#include "include/transactions/returnbook.h"
#include "ui_returnbook.h"

ReturnBook::ReturnBook(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ReturnBook)
{
    ui->setupUi(this);
    issueBookAccessNo = "0";
    ptrMessageBox = new MessageBox();
}

ReturnBook::~ReturnBook()
{
    delete ui;
    delete ptrMessageBox;
}

void ReturnBook::Show(){
    this->show();
}

void ReturnBook::on_returnButton_clicked()
{
    QSqlQuery query(MyDB::getInstance()->getDBInstance());
    query.clear();

    QString returnDate = ui->txtReturnDate->text();
    query.prepare("update issued_books set return_date='" + returnDate + "' where access_no = '" + issueBookAccessNo + "'");

    if(!query.exec())
    {
        ptrMessageBox->setText("Failed to return book");
        ptrMessageBox->setTitle("Failed");
        ptrMessageBox->Show();
    }
    else
    {
        if(query.numRowsAffected() > 0)
        {
            ptrMessageBox->setText("Book returned successfully");
            ptrMessageBox->setTitle("Success");
            ptrMessageBox->Show();
            this->close();
        }
        else{
            ptrMessageBox->setText("Failed to return book");
            ptrMessageBox->setTitle("Failed");
            ptrMessageBox->Show();
        }
    }
    this->close();
}


void ReturnBook::on_cancelButton_clicked()
{
    this->close();
}

