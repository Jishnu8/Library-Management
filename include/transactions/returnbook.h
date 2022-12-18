#ifndef RETURNBOOK_H
#define RETURNBOOK_H

#include <QMainWindow>
#include "include/dialog_box/messagebox.h"
#include <include/mydb.h>

namespace Ui {
class ReturnBook;
}

class ReturnBook : public QMainWindow
{
    Q_OBJECT

public:
    explicit ReturnBook(QWidget *parent = nullptr);
    ~ReturnBook();
    void Show();
    QString issueBookAccessNo;

private slots:
    void on_returnButton_clicked();

    void on_cancelButton_clicked();

private:
    Ui::ReturnBook *ui;
    MessageBox *ptrMessageBox;
};

#endif // RETURNBOOK_H
