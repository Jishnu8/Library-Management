#ifndef SEARCHUSER_H
#define SEARCHUSER_H

#include <QMainWindow>
#include "include/mydb.h"
#include "include/users/edituser.h"
#include <QTableWidgetItem>
#include <QMessageBox>
#include "include/dialog_box/messagebox.h"
#include "include/dialog_box/criticalmsgbox.h"

namespace Ui {
class SearchUser;
}

class SearchUser : public QMainWindow
{
    Q_OBJECT

public:
    explicit SearchUser(QWidget *parent = nullptr);
    ~SearchUser();
    void Show();
    void verticalHeaderVisibility(bool);
    void setEditClickEvent(bool);
    void setDeleteClickEvent(bool);

private slots:

    void on_searchButton_clicked();

private:
    Ui::SearchUser *ui;
    EditUser *ptrEditUser;
    MessageBox *ptrMessageBox;
    CriticalMsgBox *ptrMsgBox2;
    void editClickEvent();
    void deleteClickEvent();
    void deleteEvent();
    void searchClickEvent();
    void resetLineEditText();
    bool checkIssuedBooksList(QString userAccessNo);
    friend class IssueBook;
};

#endif // SEARCHUSER_H
