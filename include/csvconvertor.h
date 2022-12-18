#ifndef CSVCONVERTOR_H
#define CSVCONVERTOR_H

#include <QMainWindow>
#include "mydb.h"
#include "include/dialog_box/messagebox.h"
#include <fstream>

namespace Ui {
class CsvConvertor;
}

class CsvConvertor : public QMainWindow
{
    Q_OBJECT

public:
    explicit CsvConvertor(QWidget *parent = nullptr, QString="select * from books",QString* = nullptr, int = 0);
    ~CsvConvertor();
    void Show();

private slots:
    void on_cancelButton_clicked();

    void on_saveButton_clicked();

private:
    Ui::CsvConvertor *ui;
    void sqlToCsv();
    QString getFilePath();
    QString sqlQuery;
    QString* rowHeaders;
    int rowHeadersSize;
    MessageBox *ptrMessageBox ;
};

#endif // CSVCONVERTOR_H
