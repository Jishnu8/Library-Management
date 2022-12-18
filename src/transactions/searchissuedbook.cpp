#include "include/transactions/searchissuedbook.h"
#include "ui_searchissuedbook.h"

SearchIssuedBook::SearchIssuedBook(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SearchIssuedBook)
{
    ui->setupUi(this);
    ptrReturnBook = new ReturnBook(this);
}

SearchIssuedBook::~SearchIssuedBook()
{
    delete ui;
}

void SearchIssuedBook::Show()
{
    resetLineEditText();
    searchClickEvent();
    this->show();

}

void SearchIssuedBook::returnClickEvent(){
    QModelIndexList selection = ui->bookSearchTable->selectionModel()->selectedRows();
    int row = selection.at(0).row();
    QModelIndex index = ui->bookSearchTable->model()->index(row,0);
    QString issueBookAccessNo = ui->bookSearchTable->model()->data(index).toString();
    ptrReturnBook->issueBookAccessNo = issueBookAccessNo;
    ptrReturnBook->Show();
}


void SearchIssuedBook::setReturnClickEvent(){
    connect(ui->bookSearchTable->verticalHeader(), &QHeaderView::sectionClicked, this, &SearchIssuedBook::returnClickEvent);
}


void SearchIssuedBook::verticalHeaderVisibility(bool a){
    ui->bookSearchTable->verticalHeader()->setVisible(a);
}

void SearchIssuedBook::searchClickEvent(){
    QString accessNo = ui->txtAccessNo->text();
    QString bookName = ui->txtBookName->text();
    QString authorName = ui->txtAuthor1Name->text();
    QString username = ui->txtUsername->text();
    QString command = "select * from issued_books where 1=1";

    if (!accessNo.isEmpty()){
        command.append(" and access_no=" +accessNo+"");
    }
    if (!bookName.isEmpty()){
        command.append(" and book_name='" + bookName + "'");
    }
    if (!authorName.isEmpty()){
        command.append(" and author_name='" + authorName + "'");
    }
    if (!username.isEmpty()){
        command.append(" and username='" + username + "'");
    }


    QSqlQueryModel * model = new QSqlQueryModel(this);
    QSqlQuery query( MyDB::getInstance()->getDBInstance());
    query.prepare(command);

    if(!query.exec())
       qDebug() << query.lastError().text() << query.lastQuery();
    else
       qDebug() << "== success query fetch()";

    model->setQuery(query);
    ui->bookSearchTable->setModel(model);
    ui->bookSearchTable->horizontalHeader()->setFixedHeight(35);
    ui->bookSearchTable->show();
}

void SearchIssuedBook::on_searchButton_clicked()
{
    searchClickEvent();
}

void SearchIssuedBook::resetLineEditText(){
    ui->txtAccessNo->clear();
    ui->txtBookName->clear();
    ui->txtAuthor1Name->clear();
    ui->txtUsername->clear();
}

