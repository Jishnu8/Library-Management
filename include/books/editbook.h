#ifndef EDITBOOK_H
#define EDITBOOK_H

#include <QDialog>
#include <QMessageBox>
#include "include/dialog_box/messagebox.h"
#include "include/mydb.h"

namespace Ui {
class EditBook;
}

class EditBook : public QDialog
{
    Q_OBJECT

public:
    explicit EditBook(QWidget *parent = nullptr);
    ~EditBook();
    QString id;
    void Show();
    void resetElements();
    void setLineEditText(QString bookName="", QString author1Name="", QString author2Name="",
                         QString DOP="", QString Edition="", QString ClassificationNo="",
                         QString NoOfPages="", QString DateOfAcquistion="", QString Comments="");

private slots:
    void on_btnReset_clicked();

    void on_btnEdit_clicked();

private:
    Ui::EditBook *ui;
    MessageBox *ptrMessageBox;
    QString *allItems;
};

#endif // EDITBOOK_H
