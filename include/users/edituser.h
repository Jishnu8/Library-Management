#ifndef EDITUSER_H
#define EDITUSER_H

#include <QDialog>
#include "include/dialog_box/messagebox.h"
#include "include/mydb.h"

namespace Ui {
class EditUser;
}

class EditUser : public QDialog
{
    Q_OBJECT

public:
    explicit EditUser(QWidget *parent = nullptr);
    ~EditUser();
    QString id;
    void Show();
    void resetElements();
    void setLineEditText(QString fullName="", QString username="", QString password="",
                         QString phoneNo="", QString emailId="", QString address="",
                         QString comments="");

private slots:
    void on_btnReset_clicked();

    void on_btnEdit_clicked();

private:
    Ui::EditUser *ui;
    MessageBox *ptrMessageBox;
    QString *allItems;
};

#endif // EDITUSER_H
