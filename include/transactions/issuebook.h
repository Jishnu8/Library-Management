#ifndef ISSUEBOOK_H
#define ISSUEBOOK_H

#include <QMainWindow>
#include <include/books/searchbook.h>
#include <include/users/searchuser.h>
#include <sstream>
#include "include/dialog_box/messagebox.h"
#include <vector>

namespace Ui {
class IssueBook;
}

class IssueBook : public QMainWindow
{
    Q_OBJECT

public:
    explicit IssueBook(QWidget *parent = nullptr);
    ~IssueBook();
    void Show();

private slots:
    void on_searchBook_clicked();

    void on_searchUser_clicked();

    int on_issueButton_clicked();

private:
    Ui::IssueBook *ui;
    SearchBook *pntrSearchBook;
    SearchUser *pntrSearchUser;
    MessageBox *ptrMessageBox;
    void setIssueBookClickEvent();
    void issueBookClickEvent();
    void setIssueUserClickEvent();
    void issueUserClickEvent();
    int getBookAccessNo(QSqlQuery, QString, QString);
    int getUserAccessNo(QSqlQuery, QString);
    bool checkIssuedBooksList(QString);
    void resetLineEditText();
    std::vector<int> getListOfIssuedBooks();
    std::vector<int> getBookAccessNoToRowNo();
};

#endif // ISSUEBOOK_H
