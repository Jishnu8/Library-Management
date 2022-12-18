#ifndef PRINT_H
#define PRINT_H

#include <QMainWindow>
#include <QDialog>
#include "mydb.h"
#include <QtCore>

namespace Ui {
class Print;
}

class Print : public QMainWindow
{
    Q_OBJECT

public:
    explicit Print(QWidget *parent = nullptr, QString *headers=nullptr, int size=0);
    ~Print();
    void Show(QString message);

private:
    Ui::Print *ui;
    void updateUI(QString message);
    QString* rowHeaders;
    int rowHeadersSize;

};

#endif // PRINT_H
