#include "include/books/searchbook.h"
#include "ui_criticalmsgbox.h"
#include "ui_searchbook.h"

SearchBook::SearchBook(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SearchBook)
{
    ui->setupUi(this);
    ptrEditBook = new EditBook(this);
    ptrMessageBox = new MessageBox(this);
    ptrMsgBox2 = new CriticalMsgBox(this);
}

SearchBook::~SearchBook()
{
    delete ptrMessageBox;
    delete ptrMsgBox2;
    delete ui;
}

void SearchBook::Show()
{
    resetLineEditText();
    searchClickEvent();
    this->show();

}

void SearchBook::editClickEvent(){
    QModelIndexList selection = ui->bookSearchTable->selectionModel()->selectedRows();
    int row = selection.at(0).row();
    QModelIndex index;
    QString cellData;
    int columnCount = ui->bookSearchTable->model()->columnCount();
    QString rowData[columnCount];

    for (int i = 0; i < columnCount; i++){
        index =  ui->bookSearchTable->model()->index(row,i);
        cellData = ui->bookSearchTable->model()->data(index).toString();
        rowData[i] = cellData;
    }

    ptrEditBook->setLineEditText(rowData[1], rowData[2], rowData[3], rowData[4], rowData[5], rowData[6], rowData[7], rowData[8], rowData[9]);
    ptrEditBook->id = rowData[0];
    ptrEditBook->Show();
}


void SearchBook::setEditClickEvent(bool a){
    if (a == true){
        connect(ui->bookSearchTable->verticalHeader(), &QHeaderView::sectionClicked, this, &SearchBook::editClickEvent);
    }
    else{
         disconnect(ui->bookSearchTable->verticalHeader(), &QHeaderView::sectionClicked, this, &SearchBook::editClickEvent);
    }
}

void SearchBook::deleteEvent(){
    if(ptrMsgBox2->execute == true){
        qDebug() << "dsafnsdj";
        QModelIndexList selection = ui->bookSearchTable->selectionModel()->selectedRows();
        int row = selection.at(0).row();
        QModelIndex index =  ui->bookSearchTable->model()->index(row,0);
        QString accessNo = ui->bookSearchTable->model()->data(index).toString();
        bool a = checkIssuedBooksList(accessNo);

        if (a == true){
            QSqlQuery query(MyDB::getInstance()->getDBInstance());
            query.clear();
            query.prepare("delete from books where access_no='" + accessNo + "'");
            if(!query.exec())
            {
                qDebug() << query.lastError().text() << query.lastQuery();
                ptrMessageBox->setText("Failed to Delete Item");
                ptrMessageBox->setTitle("Failure");
                ptrMessageBox->Show();
            }
            else
            {
                if(query.numRowsAffected() > 0)
                {
                    qDebug() <<"read was successful "<< query.lastQuery();
                    ptrMessageBox->setText("Item Deleted Successfully");
                    ptrMessageBox->setTitle("Success");
                    ptrMessageBox->Show();
                    this->close();
                }
                else
                    qDebug() <<"Unable to Delete Item";
            }
        }
        else{
            ptrMessageBox->setText("Failed to delete book as it's issued");
            ptrMessageBox->setTitle("Failure");
            ptrMessageBox->Show();
        }
    }
    ptrMsgBox2->execute = false;
}

void SearchBook::deleteClickEvent(){
    QObject::connect(ptrMsgBox2->ui->okButton,&QPushButton::clicked, this, &SearchBook::deleteEvent);
    ptrMsgBox2->Show();
}

void SearchBook::setDeleteClickEvent(bool a){
    if (a == true){
        connect(ui->bookSearchTable->verticalHeader(), &QHeaderView::sectionClicked, this, &SearchBook::deleteClickEvent);
    }
    else{
        disconnect(ui->bookSearchTable->verticalHeader(), &QHeaderView::sectionClicked, this, &SearchBook::deleteClickEvent);
    }
}

void SearchBook::verticalHeaderVisibility(bool a){
    ui->bookSearchTable->verticalHeader()->setVisible(a);
}

void SearchBook::searchClickEvent(){
    QString accessNo = ui->txtAccessNo->text();
    QString bookName = ui->txtBookName->text();
    QString author1Name = ui->txtAuthor1Name->text();
    QString author2Name = ui->txtAuthor2Name->text();
    QString command = "select * from books where 1=1";

    if (!accessNo.isEmpty()){
        command.append(" and access_no=" +accessNo+"");
    }
    if (!bookName.isEmpty()){
        command.append(" and book_name='" + bookName + "'");
    }
    if (!author1Name.isEmpty()){
        command.append(" and (author1_name='" + author1Name + "' or author2_name='" + author1Name + "')");
    }
    if (!author2Name.isEmpty()){
        command.append(" and (author1_name='" + author2Name + "' or author2_name='" + author2Name + "')");
    }


    QSqlQueryModel * model = new QSqlQueryModel(this);
    QSqlQuery query( MyDB::getInstance()->getDBInstance());
    query.prepare(command);

    if(!query.exec())
       qDebug() << query.lastError().text() << query.lastQuery();
    else
       qDebug() << "== success query fetch()";

    while(query.next())
    qDebug()<<query.value(0).toString();

    model->setQuery(query);
    ui->bookSearchTable->horizontalHeader()->setFixedHeight(35);
    ui->bookSearchTable->setModel(model);
    ui->bookSearchTable->show();
}

void SearchBook::on_searchButton_clicked()
{
    searchClickEvent();
}

void SearchBook::resetLineEditText(){
    ui->txtAccessNo->clear();
    ui->txtBookName->clear();
    ui->txtAuthor1Name->clear();
    ui->txtAuthor2Name->clear();
}

bool SearchBook::checkIssuedBooksList(QString bookAccessNo){
    QSqlQuery query2(MyDB::getInstance()->getDBInstance());
    query2.clear();
    QString command = "select * from issued_books where book_access_no='" +bookAccessNo +"'";
    qDebug() << bookAccessNo;

    query2.prepare(command);
    if(!query2.exec())
       qDebug() << query2.lastError().text() << query2.lastQuery();
    else
       qDebug() << "== success query fetch()";

    while(query2.next()){
        if (query2.value(7).isNull() == true){
            return false;
        }
    }

    return true;
}

