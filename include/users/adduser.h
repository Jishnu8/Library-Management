#ifndef ADDUSER_H
#define ADDUSER_H

#include <QDialog>
#include "include/dialog_box/messagebox.h"
#include "include/mydb.h"

namespace Ui {
class AddUser;
}

class AddUser : public QDialog
{
    Q_OBJECT

public:
    explicit AddUser(QWidget *parent = nullptr);
    ~AddUser();
    void Show();
    void resetElements();

private slots:
    void on_btnAdd_clicked();

    void on_btnReset_clicked();

private:
    Ui::AddUser *ui;
    MessageBox *ptrMessageBox;
};

#endif // ADDUSER_H
