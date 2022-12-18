#include "include/transactions/issuebook.h"
#include "qpainter.h"
#include "ui_issuebook.h"
#include "ui_searchbook.h"
#include "ui_searchuser.h"

IssueBook::IssueBook(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::IssueBook)
{
    ui->setupUi(this);
    pntrSearchBook = new SearchBook();
    pntrSearchUser = new SearchUser();
    ptrMessageBox = new MessageBox();
}

IssueBook::~IssueBook()
{
    delete ui;
    delete pntrSearchBook;
    delete pntrSearchUser;
    delete ptrMessageBox;
}

void IssueBook::Show(){
    QPixmap pixmap(":/search.jpg");
    QIcon ButtonIcon(pixmap);
    ui->searchBook->setIcon(ButtonIcon);
    ui->searchBook->setIconSize(pixmap.rect().size());
    ui->searchUser->setIcon(ButtonIcon);
    ui->searchUser->setIconSize(pixmap.rect().size());
    this->show();
}

void IssueBook::issueBookClickEvent(){
        QModelIndexList selection = pntrSearchBook->ui->bookSearchTable->selectionModel()->selectedRows();
        int row = selection.at(0).row();
        QModelIndex bookNameIndex = pntrSearchBook->ui->bookSearchTable->model()->index(row,1);
        QString issueBookName = pntrSearchBook->ui->bookSearchTable->model()->data(bookNameIndex).toString();
        QModelIndex authorNameIndex = pntrSearchBook->ui->bookSearchTable->model()->index(row,2);
        QString issueAuthorName = pntrSearchBook->ui->bookSearchTable->model()->data(authorNameIndex).toString();
        ui->txtBookName->setText(issueBookName);
        ui->txtAuthorName->setText(issueAuthorName);
        pntrSearchBook->close();
}

void IssueBook::setIssueBookClickEvent(){
    connect(pntrSearchBook->ui->bookSearchTable->verticalHeader(), &QHeaderView::sectionClicked, this, &IssueBook::issueBookClickEvent);
}

void IssueBook::issueUserClickEvent(){
        QModelIndexList selection = pntrSearchUser->ui->userSearchTable->selectionModel()->selectedRows();
        int row = selection.at(0).row();
        QModelIndex usernameIndex = pntrSearchUser->ui->userSearchTable->model()->index(row,2);
        QString username = pntrSearchUser->ui->userSearchTable->model()->data(usernameIndex).toString();
        ui->txtUsername->setText(username);
        pntrSearchUser->close();
}

void IssueBook::setIssueUserClickEvent(){
    connect(pntrSearchUser->ui->userSearchTable->verticalHeader(), &QHeaderView::sectionClicked, this, &IssueBook::issueUserClickEvent);
}


void IssueBook::on_searchBook_clicked()
{
    pntrSearchBook->verticalHeaderVisibility(true);
    setIssueBookClickEvent();
    pntrSearchBook->Show();
    std::vector<int> listOfIssueBookAccessNo = getListOfIssuedBooks();
    std::vector<int> listOfBookAccessNoToRowNo = getBookAccessNoToRowNo();

    //hide all the rows for which books have already been issued
    for (auto element : listOfIssueBookAccessNo) {
        pntrSearchBook->ui->bookSearchTable->hideRow(listOfBookAccessNoToRowNo[element - 1] - 1);
    }
}


void IssueBook::on_searchUser_clicked()
{
    pntrSearchUser->verticalHeaderVisibility(true);
    setIssueUserClickEvent();
    pntrSearchUser->Show();
}

int IssueBook::getBookAccessNo(QSqlQuery query, QString bookName, QString authorName){
    QString command = "select * from books where 1=1";

    if (!bookName.isEmpty()){
        command.append(" and book_name='" + bookName + "'");
    }
    if (!authorName.isEmpty()){
        command.append(" and (author1_name='" + authorName + "' or author2_name='" + authorName + "')");
    }

    query.prepare(command);
    if(!query.exec())
       qDebug() << query.lastError().text() << query.lastQuery();
    else
       qDebug() << "== success query fetch()";

    int access_no = -2;
    int count = 0;

    while(query.next()){
        count += 1;
        if (count > 1){
            return -1;
        }
        access_no = query.value(0).toInt();
    }

    return access_no;
}

int IssueBook::getUserAccessNo(QSqlQuery query, QString username){
    QString command = "select * from users where 1=1";

    if (!username.isEmpty()){
        command.append(" and username='" + username + "'");
    }

    query.prepare(command);
    if(!query.exec())
       qDebug() << query.lastError().text() << query.lastQuery();
    else
       qDebug() << "== success query fetch()";

    int access_no = -2;
    int count = 0;

    while(query.next()){
        count += 1;
        if (count > 1){
            return -1;
        }
        access_no = query.value(0).toInt();
    }

    return access_no;
}

bool IssueBook::checkIssuedBooksList(QString bookAccessNo){
    QSqlQuery query2(MyDB::getInstance()->getDBInstance());
    query2.clear();
    QString command = "select * from issued_books where book_access_no='" +bookAccessNo +"'";

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

std::vector<int> IssueBook::getListOfIssuedBooks(){
    std::vector<int> listOfIssueBookAccessNo {};

    QSqlQuery query2(MyDB::getInstance()->getDBInstance());
    query2.clear();
    QString command = "select * from issued_books";

    query2.prepare(command);
    if(!query2.exec())
       qDebug() << query2.lastError().text() << query2.lastQuery();
    else
       qDebug() << "== success query fetch()";

    while(query2.next()){
        if (query2.value(7).isNull() == true){
            listOfIssueBookAccessNo.insert(listOfIssueBookAccessNo.end(), query2.value(3).toInt());
        }
    }

    return listOfIssueBookAccessNo;
}

std::vector<int> IssueBook::getBookAccessNoToRowNo(){
    std::vector<int> listOfBookAccessNoToRowNo {};

    QSqlQuery query2(MyDB::getInstance()->getDBInstance());
    query2.clear();
    QString command = "select * from books";

    query2.prepare(command);
    if(!query2.exec())
       qDebug() << query2.lastError().text() << query2.lastQuery();
    else
       qDebug() << "== success query fetch()";

    int prev = 1;
    int temp = 1;
    while(query2.next()){
        for (int i = prev; i < query2.value(0).toInt(); i++){
            listOfBookAccessNoToRowNo.insert(listOfBookAccessNoToRowNo.end(), 0);
        }

        listOfBookAccessNoToRowNo.insert(listOfBookAccessNoToRowNo.end(), temp);
        prev = query2.value(0).toInt() + 1;
        temp += 1;
    }

    return listOfBookAccessNoToRowNo;
}

int IssueBook::on_issueButton_clicked()
{
    QMessageBox msgBox;
    QSqlQuery query(MyDB::getInstance()->getDBInstance());
    query.clear();

    QString bookName = ui->txtBookName->text();
    QString authorName = ui->txtAuthorName->text();
    QString username = ui->txtUsername->text();
    QString issueDate = ui->txtIssueDate->text();
    QString comments = ui->txtComments->text();

    int bookAccessNo = getBookAccessNo(query, bookName, authorName);
    if (bookAccessNo == -2){
        ptrMessageBox->setText("No book found");
        ptrMessageBox->setTitle("Failed");
        ptrMessageBox->Show();
        return 0;
    }
    if (bookAccessNo == -1){
        ptrMessageBox->setText("Multiple books found");
        ptrMessageBox->setTitle("Failed");
        ptrMessageBox->Show();
        return 0;
    }
    query.clear();

    int userAccessNo = getUserAccessNo(query, username);
    if (userAccessNo == -2){
        ptrMessageBox->setText("No user found");
        ptrMessageBox->setTitle("Failed");
        ptrMessageBox->Show();
        return 0;
    }
    if (userAccessNo == -1){
        ptrMessageBox->setText("Multiple users found");
        ptrMessageBox->setTitle("Failed");
        ptrMessageBox->Show();
        return 0;
    }
    query.clear();

    std::ostringstream str1;
    str1 << bookAccessNo;
    QString bookAccessNum = QString::fromStdString(str1.str());
    std::ostringstream str2;
    str2 << userAccessNo;
    QString userAccessNum = QString::fromStdString(str2.str());

    if (checkIssuedBooksList(bookAccessNum) == false){
        ptrMessageBox->setText("Book has already been issued");
        ptrMessageBox->setTitle("Failed");
        ptrMessageBox->Show();
        return 0;
    }

    query.prepare("insert into issued_books (user_access_no, username, book_access_no, book_name, author_name, issue_date, comments) values ('" +userAccessNum +"', '" +username +"', '" +bookAccessNum +"', '" +bookName +"', '" +authorName +"', '" +issueDate +"', '" +comments +"')");
    if(!query.exec())
    {
        qDebug() << query.lastError().text() << query.lastQuery();
        ptrMessageBox->setText("Failed to Issue Book");
        ptrMessageBox->setTitle("Failed");
    }
    else
    {
        if(query.numRowsAffected() > 0)
        {
            qDebug() <<"read was successful "<< query.lastQuery();
            ptrMessageBox->setText("Book Issued Successfully");
            ptrMessageBox->setTitle("Success");
        }
        else
            qDebug() <<"Unable to Issue Book";
    }

    ptrMessageBox->Show();
    resetLineEditText();
}

void IssueBook::resetLineEditText(){
    ui->txtBookName->clear();
    ui->txtAuthorName->clear();
    ui->txtUsername->clear();
    ui->txtComments->clear();
    ui->txtIssueDate->clear();
}

