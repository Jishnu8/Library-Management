#ifndef SEARCHBOOK_H
#define SEARCHBOOK_H

#include <QMainWindow>
#include <QObject>
#include "include/mydb.h"
#include "editbook.h"
#include <QTableWidgetItem>
#include "include/dialog_box/messagebox.h"
#include "include/dialog_box/criticalmsgbox.h"

namespace Ui {
class SearchBook;
}

class SearchBook : public QMainWindow
{
    Q_OBJECT

public:
    explicit SearchBook(QWidget *parent = nullptr);
    ~SearchBook();
    void Show();
    void verticalHeaderVisibility(bool);
    void setEditClickEvent(bool);
    void setDeleteClickEvent(bool);

private slots:

    void on_searchButton_clicked();

private:
    Ui::SearchBook *ui;
    EditBook *ptrEditBook;
    MessageBox *ptrMessageBox;
    CriticalMsgBox *ptrMsgBox2;
    void editClickEvent();
    void deleteClickEvent();
    void deleteEvent();
    void searchClickEvent();
    void resetLineEditText();
    bool checkIssuedBooksList(QString bookAccessNo);
    friend class IssueBook;
};

#endif // SEARCHBOOK_H
