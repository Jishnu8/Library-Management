#include "include/books/editbook.h"
#include "ui_editbook.h"
#include <string>

using namespace std;

EditBook::EditBook(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditBook)
{
    ui->setupUi(this);
    id = "1";
    ptrMessageBox = new MessageBox();
}

EditBook::~EditBook()
{
    delete ui;
    delete ptrMessageBox;
}

void EditBook::Show()
{
    this->show();
}

void EditBook::resetElements(){
    ui->txtBookName->setText(allItems[0]);
    ui->txtAuthor1Name->setText(allItems[1]);
    ui->txtAuthor2Name->setText(allItems[2]);
    ui->txtDOP->setText(allItems[3]);
    ui->txtEdition->setText(allItems[4]);
    ui->txtClassificationNo->setText(allItems[5]);
    ui->txtPages->setText(allItems[6]);
    ui->txtDateOfAcquisition->setText(allItems[7]);
    ui->txtComments->setText(allItems[8]);
}

void EditBook::setLineEditText(QString bookName, QString author1Name, QString author2Name,
                               QString DOP, QString Edition, QString ClassificationNo,
                               QString NoOfPages, QString DateOfAcquistion, QString Comments){
    ui->txtBookName->setText(bookName);
    ui->txtAuthor1Name->setText(author1Name);
    ui->txtAuthor2Name->setText(author2Name);
    ui->txtDOP->setText(DOP);
    ui->txtEdition->setText(Edition);
    ui->txtClassificationNo->setText(ClassificationNo);
    ui->txtPages->setText(NoOfPages);
    ui->txtDateOfAcquisition->setText(DateOfAcquistion);
    ui->txtComments->setText(Comments);

    allItems = new QString[9];
    allItems[0] = bookName; allItems[1] = author1Name; allItems[2] = author2Name, allItems[3] = DOP; allItems[4] = Edition;
    allItems[5] = ClassificationNo; allItems[6] = NoOfPages, allItems[7] = DateOfAcquistion; allItems[8] = Comments;
}

void EditBook::on_btnReset_clicked()
{
    resetElements();
}


void EditBook::on_btnEdit_clicked()
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

    query.prepare("update books set book_name='" + bookName + "', author1_name='" + author1Name + "', author2_name='" + author2Name + "', date_of_publication='" + DOP + "', edition='" + edition + "', classification_no='" + classificationNo + "', pages='" + pages + "', date_of_acquisition='" + dateOfAcquisition + "', comments='" + comments + "' where access_no = '" + id + "'");
    if(!query.exec())
    {
        qDebug() << query.lastError().text() << query.lastQuery();
        ptrMessageBox->setText("Failed to Edit Item");
        ptrMessageBox->setTitle("Failed");
        ptrMessageBox->Show();
    }
    else
    {
        if(query.numRowsAffected() > 0)
        {
            qDebug() <<"read was successful "<< query.lastQuery();
            ptrMessageBox->setText("Item Edited Successfully");
            ptrMessageBox->setTitle("Success");
            resetElements();
            ptrMessageBox->Show();
            this->close();
        }
        else
            qDebug() <<"Unable to Edit new Item";
    }
}

