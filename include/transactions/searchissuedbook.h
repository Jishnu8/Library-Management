#ifndef SEARCHISSUEDBOOK_H
#define SEARCHISSUEDBOOK_H

#include <QMainWindow>
#include "include/mydb.h"
#include "returnbook.h"
#include <QTableWidgetItem>

namespace Ui {
class SearchIssuedBook;
}

class SearchIssuedBook : public QMainWindow
{
    Q_OBJECT

public:
    explicit SearchIssuedBook(QWidget *parent = nullptr);
    ~SearchIssuedBook();
    void Show();
    void verticalHeaderVisibility(bool);
    void setReturnClickEvent();

private slots:

    void on_searchButton_clicked();

private:
    Ui::SearchIssuedBook *ui;
    ReturnBook *ptrReturnBook;
    void returnClickEvent();
    void searchClickEvent();
    void resetLineEditText();
};

#endif // SEARCHISSUEDBOOK_H
