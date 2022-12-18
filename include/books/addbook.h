#ifndef ADDBOOK_H
#define ADDBOOK_H

#include <QDialog>
#include "include/dialog_box/messagebox.h"
#include "include/books/classificationno.h"
#include "include/mydb.h"

namespace Ui {
class AddBook;
}

class AddBook : public QDialog
{
    Q_OBJECT

public:
    explicit AddBook(QWidget *parent = nullptr);
    ~AddBook();
    void Show();
    void resetElements();

private slots:
    void on_btnAdd_clicked();

    void on_btnReset_clicked();

    void on_classificationNoButton_clicked();

private:
    Ui::AddBook *ui;
    ClassificationNo *ptrClassificationNo;
    MessageBox *ptrMessageBox;
};

#endif // ADDBOOK_H
