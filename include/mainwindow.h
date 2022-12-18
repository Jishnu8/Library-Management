#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <include/books/addbook.h>
#include <include/books/searchbook.h>
#include <include/print.h>
#include <include/csvconvertor.h>
#include <include/users/adduser.h>
#include <include/users/searchuser.h>
#include <include/transactions/issuebook.h>
#include <include/transactions/searchissuedbook.h>
#include "calendar.h"
#include <ctime>
#include <vector>
#include <string.h>
#include <QFontDatabase>
#include <QTreeWidget>

#include <QPixmap>
#include <QPainter>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_addBook_triggered();

    void on_searchBook_triggered();

    void on_editBook_triggered();

    void on_deleteBook_triggered();


    void on_print_by_Id_triggered();

    void on_print_by_author_triggered();

    void on_print_by_book_triggered();

    void on_csv_by_Id_triggered();

    void on_csv_by_authorName_triggered();

    void on_csv_by_bookName_triggered();

    void on_addUser_triggered();

    void on_searchUser_triggered();

    void on_deleteUser_triggered();

    void on_editUser_triggered();


    void on_printUsersById_triggered();

    void on_printUsersByName_triggered();

    void on_csvExportUsersById_triggered();

    void on_csvExportUsersByName_triggered();

    void on_issueBook_triggered();

    void on_quitButton_clicked();

    void on_pushButton_clicked();

    void on_actionReturn_Book_triggered();

    void on_pushButton_2_clicked();

    void on_print_issued_books_triggered();

    void on_export_as_csv_issued_books_triggered();

    void on_print_overdue_books_triggered();

    void on_export_as_csv_overdue_books_triggered();

private:
    Ui::MainWindow *ui;
    AddBook *ptrAddBook;
    SearchBook *ptrSearchBook;
    Print *ptrPrint;
    AddUser *ptrAddUser;
    SearchUser *ptrSearchUser;
    CsvConvertor *ptrCsvConvertor;
    IssueBook *ptrIssueBook;
    SearchIssuedBook *ptrSearchIssuedBook;
    int maxBorrowDays;
    void updateOverdueList();
};
#endif // MAINWINDOW_H
