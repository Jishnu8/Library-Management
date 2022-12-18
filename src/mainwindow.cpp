#include "include/mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ptrAddBook = new AddBook(this);
    ptrSearchBook = new SearchBook(this);
    ptrPrint = new Print(this);
    ptrSearchBook = new SearchBook(this);
    ptrAddUser = new AddUser(this);
    ptrSearchUser = new SearchUser(this);
    ptrCsvConvertor = new CsvConvertor(this);
    ptrIssueBook = new IssueBook(this);
    ptrSearchIssuedBook = new SearchIssuedBook(this);
    maxBorrowDays = 14;

    QPixmap bkgnd(":/library.jpg");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Window, bkgnd);
    this->setPalette(palette);

    //this->centralWidget()->setStyleSheet("background-image:url(/home/jis/Qt_projects/LibraryManagement/data/library/jpg); background-position: center; ");
}

MainWindow::~MainWindow()
{
    delete ui;
    delete ptrAddBook;
    delete ptrPrint;
    delete ptrSearchBook;
    delete ptrAddUser;
    delete ptrSearchUser;
    delete ptrCsvConvertor;
    delete ptrIssueBook;
    delete ptrSearchIssuedBook;
}


void MainWindow::on_addBook_triggered()
{
    ptrAddBook->Show();
}



void MainWindow::on_searchBook_triggered()
{
    ptrSearchBook->verticalHeaderVisibility(false);
    ptrSearchBook->Show();
}


void MainWindow::on_editBook_triggered()
{
    ptrSearchBook->verticalHeaderVisibility(true);
    ptrSearchBook->setDeleteClickEvent(false);
    ptrSearchBook->setEditClickEvent(true);
    ptrSearchBook->Show();
}


void MainWindow::on_deleteBook_triggered()
{
    ptrSearchBook->verticalHeaderVisibility(true);
    ptrSearchBook->setEditClickEvent(false);
    ptrSearchBook->setDeleteClickEvent(true);
    ptrSearchBook->Show();
}


void MainWindow::on_print_by_Id_triggered()
{
    QString query = "select * from books order by access_no";
    delete ptrPrint;
    QString rowHeader[10] = {"Access No", "Book Name", "Author1 Name", "Author2 Name", "Date of Publication", "Edition", "Classification No",
                            "Pages", "Date Of Acquisition", "Comments"};
    ptrPrint = new Print(this, rowHeader, 10);
    ptrPrint->Show(query);
}


void MainWindow::on_print_by_author_triggered()
{
    QString query = "select * from books order by author1_name";
    delete ptrPrint;
    QString rowHeader[10] = {"Access No", "Book Name", "Author1 Name", "Author2 Name", "Date of Publication", "Edition", "Classification No",
                            "Pages", "Date Of Acquisition", "Comments"};
    ptrPrint = new Print(this, rowHeader, 10);
    ptrPrint->Show(query);
}


void MainWindow::on_print_by_book_triggered()
{
    QString query = "select * from books order by book_name";
    delete ptrPrint;
    QString rowHeader[10] = {"Access No", "Book Name", "Author1 Name", "Author2 Name", "Date of Publication", "Edition", "Classification No",
                            "Pages", "Date Of Acquisition", "Comments"};
    ptrPrint = new Print(this, rowHeader, 10);
    ptrPrint->Show(query);
}


void MainWindow::on_csv_by_Id_triggered()
{
    delete ptrCsvConvertor;
    QString rowHeader[10] = {"Access No", "Book Name", "Author1 Name", "Author2 Name", "Date of Publication", "Edition", "Classification No",
                            "Pages", "Date Of Acquisition", "Comments"};
    ptrCsvConvertor = new CsvConvertor(this, "select * from books order by access_no", rowHeader, 10);
    ptrCsvConvertor->Show();
}


void MainWindow::on_csv_by_authorName_triggered()
{
    delete ptrCsvConvertor;
    QString rowHeader[10] = {"Access No", "Book Name", "Author1 Name", "Author2 Name", "Date of Publication", "Edition", "Classification No",
                            "Pages", "Date Of Acquisition", "Comments"};
    ptrCsvConvertor = new CsvConvertor(this, "select * from books order by author1_name", rowHeader, 10);
    ptrCsvConvertor->Show();
}


void MainWindow::on_csv_by_bookName_triggered()
{
    delete ptrCsvConvertor;
    QString rowHeader[10] = {"Access No", "Book Name", "Author1 Name", "Author2 Name", "Date of Publication", "Edition", "Classification No",
                            "Pages", "Date Of Acquisition", "Comments"};
    ptrCsvConvertor = new CsvConvertor(this, "select * from books order by book_name", rowHeader, 10);
    ptrCsvConvertor->Show();
}


void MainWindow::on_addUser_triggered()
{
    ptrAddUser->Show();
}


void MainWindow::on_searchUser_triggered()
{
    ptrSearchUser->verticalHeaderVisibility(false);
    ptrSearchUser->Show();
}


void MainWindow::on_deleteUser_triggered()
{
    ptrSearchUser->verticalHeaderVisibility(true);
    ptrSearchUser->setEditClickEvent(false);
    ptrSearchUser->setDeleteClickEvent(true);
    ptrSearchUser->Show();
}


void MainWindow::on_editUser_triggered()
{
    ptrSearchUser->verticalHeaderVisibility(true);
    ptrSearchUser->setDeleteClickEvent(false);
    ptrSearchUser->setEditClickEvent(true);
    ptrSearchUser->Show();
}


void MainWindow::on_printUsersById_triggered()
{
    QString query = "select * from users order by access_no";
    delete ptrPrint;
    QString rowHeader[8] = {"Access No", "Full Name", "Username", "Password", "Phone No", "Email Id", "Address",
                            "Comments"};
    ptrPrint = new Print(this, rowHeader, 8);
    ptrPrint->Show(query);
}


void MainWindow::on_printUsersByName_triggered()
{
    QString query = "select * from users order by name";
    delete ptrPrint;
    QString rowHeader[8] = {"Access No", "Full Name", "Username", "Password", "Phone No", "Email Id", "Address",
                            "Comments"};
    ptrPrint = new Print(this, rowHeader, 8);
    ptrPrint->Show(query);
}


void MainWindow::on_csvExportUsersById_triggered()
{
    delete ptrCsvConvertor;
    QString rowHeader[8] = {"Access No", "Full Name", "Username", "Password", "Phone No", "Email Id", "Address",
                            "Comments"};
    ptrCsvConvertor = new CsvConvertor(this, "select * from users order by access_no", rowHeader, 8);
    ptrCsvConvertor->Show();
}


void MainWindow::on_csvExportUsersByName_triggered()
{
    delete ptrCsvConvertor;
    QString rowHeader[8] = {"Access No", "Full Name", "Username", "Password", "Phone No", "Email Id", "Address",
                            "Comments"};
    ptrCsvConvertor = new CsvConvertor(this, "select * from users order by name", rowHeader, 8);
    ptrCsvConvertor->Show();
}


void MainWindow::on_issueBook_triggered()
{
    ptrIssueBook->Show();
}

void MainWindow::on_pushButton_clicked()
{
    ptrIssueBook->Show();
}


void MainWindow::on_quitButton_clicked()
{
    this->close();
}


void MainWindow::on_actionReturn_Book_triggered()
{
    ptrSearchIssuedBook->Show();
    ptrSearchIssuedBook->setReturnClickEvent();
}


void MainWindow::on_pushButton_2_clicked()
{
    ptrSearchIssuedBook->Show();
    ptrSearchIssuedBook->setReturnClickEvent();
}


void MainWindow::on_print_issued_books_triggered()
{
    QString query = "select * from issued_books order by access_no";
    delete ptrPrint;
    QString rowHeader[10] = {"Access No", "User Access No", "Username", "Book Access No", "Book name", "Author name", "Issue Date",
                            "Return Date", "Not Overdue", "Comments"};
    ptrPrint = new Print(this, rowHeader, 10);
    ptrPrint->Show(query);
}


void MainWindow::on_export_as_csv_issued_books_triggered()
{
    delete ptrCsvConvertor;
    QString rowHeader[10] = {"Access No", "User Access No", "Username", "Book Access No", "Book name", "Author name", "Issue Date",
                            "Return Date", "Not Overdue", "Comments"};
    ptrCsvConvertor = new CsvConvertor(this, "select * from issued_books order by access_no", rowHeader, 10);
    ptrCsvConvertor->Show();
}

void MainWindow::updateOverdueList(){
    vector<int> overdue_access_no;
    Calendar cal;
    std::time_t t = std::time(0);   // get time now
    std::tm* now = std::localtime(&t);
    Date todayDt = {now->tm_mday, now->tm_mon + 1, now->tm_year + 1900};

    QSqlQuery query( MyDB::getInstance()->getDBInstance());
    query.prepare("select * from issued_books order by access_no");

    if(!query.exec())
       qDebug() << query.lastError().text() << query.lastQuery();
    else
       qDebug() << "== success query fetch()";

    while(query.next()){
        std::string issueDate = query.value(6).toString().toStdString();
        int access_no = std::stoi(query.value(0).toString().toStdString());
        int issueDateYear = std::stoi(issueDate.substr(0,4));
        int issueDateMonth = std::stoi(issueDate.substr(5,2));
        int issueDateDay = std::stoi(issueDate.substr(8,2));
        Date issueDt = {issueDateDay, issueDateMonth, issueDateYear};
        int daysDifference = cal.getDifference(issueDt, todayDt);
        if (daysDifference > maxBorrowDays & query.value(7).isNull() == true){
            overdue_access_no.push_back(access_no);
        }
    }

    QString a = "0";
    query.clear();
    for (auto element : overdue_access_no) {
        std::ostringstream str1;
        str1 << element;
        QString element2 = QString::fromStdString(str1.str());
        query.prepare("update issued_books set is_not_overdue='" + a + "' where access_no = '" + element2 + "'");
        if(!query.exec())
           qDebug() << query.lastError().text() << query.lastQuery();
        else
           qDebug() << "== success query fetch()";

        query.clear();
    }
}


void MainWindow::on_print_overdue_books_triggered()
{
    updateOverdueList();
    QString b = "0";
    QString query2 = "select * from issued_books where is_not_overdue='" + b + "'";
    delete ptrPrint;
    QString rowHeader[10] = {"Access No", "User Access No", "Username", "Book Access No", "Book name", "Author name", "Issue Date",
                            "Return Date", "Not Overdue", "Comments"};
    ptrPrint = new Print(this, rowHeader, 10);
    ptrPrint->Show(query2);
}


void MainWindow::on_export_as_csv_overdue_books_triggered()
{
    updateOverdueList();
    QString b = "0";
    delete ptrCsvConvertor;
    QString rowHeader[10] = {"Access_no", "User Access_no", "Username", "Book Access_no", "Book name", "Author name", "Issue Date",
                            "Return Date", "is_not_overdue", "Comments"};
    ptrCsvConvertor = new CsvConvertor(this, "select * from issued_books where is_not_overdue='" + b + "'", rowHeader, 10);
    ptrCsvConvertor->Show();
}

