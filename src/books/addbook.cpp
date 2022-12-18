#include "include/books/addbook.h"
#include "ui_addbook.h"
#include <string>

using namespace std;

AddBook::AddBook(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddBook)
{
    ui->setupUi(this);
    ptrClassificationNo = new ClassificationNo(this);
    ptrMessageBox = new MessageBox(this);
}

AddBook::~AddBook()
{
    delete ui;
    delete ptrClassificationNo;
    delete ptrMessageBox;
}

void AddBook::Show()
{
    this->show();
}

void AddBook::resetElements(){
    ui->txtBookName->clear();
    ui->txtAuthor1Name->clear();
    ui->txtAuthor2Name->clear();
    ui->txtDOP->clear();
    ui->txtEdition->clear();
    ui->txtClassificationNo->clear();
    ui->txtPages->clear();
    ui->txtDateOfAcquisition->clear();
    ui->txtComments->clear();
}

void AddBook::on_btnAdd_clicked()
{
    QSqlQuery query(MyDB::getInstance()->getDBInstance());
    query.clear();

    QString bookName = ui->txtBookName->text();
    QString author1Name = ui->txtAuthor1Name->text();
    QString author2Name = ui->txtAuthor2Name->text();
    QString DOP = ui->txtDOP->text();
    QString edition = ui->txtEdition->text();
    QString classificationNo = ui->txtClassificationNo->text();
    QString pages = ui->txtPages->text();
    QString dateOfAcquisition = ui->txtDateOfAcquisition->text();
    QString comments = ui->txtComments->text();

    query.prepare("insert into books (book_name, author1_name, author2_name, date_of_publication, edition, classification_no, pages, date_of_acquisition, comments) values ('" +bookName +"', '" +author1Name +"', '" +author2Name +"', '" +DOP +"', '" +edition +"', '" +classificationNo +"', '" +pages +"', '" +dateOfAcquisition +"', '" +comments +"')");
    if(!query.exec())
    {
        qDebug() << query.lastError().text() << query.lastQuery();
        ptrMessageBox->setText("Failed to Add Item");
        ptrMessageBox->setTitle("Failed");
    }
    else
    {
        if(query.numRowsAffected() > 0)
        {
            qDebug() <<"read was successful "<< query.lastQuery();
            ptrMessageBox->setText("Item Added Successfully");
            ptrMessageBox->setTitle("Success");
            resetElements();
        }
        else
            qDebug() <<"Unable to Add new Item";
    }

    ptrMessageBox->Show();
}

void AddBook::on_btnReset_clicked()
{
    resetElements();
}




void AddBook::on_classificationNoButton_clicked()
{
    ptrClassificationNo->Show();
}

