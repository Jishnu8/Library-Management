#ifndef CLASSIFICATIONNO_H
#define CLASSIFICATIONNO_H

#include <QMainWindow>
#include <include/mydb.h>

namespace Ui {
class ClassificationNo;
}

class ClassificationNo : public QMainWindow
{
    Q_OBJECT

public:
    explicit ClassificationNo(QWidget *parent = nullptr);
    void Show();
    ~ClassificationNo();

private:
    Ui::ClassificationNo *ui;
    void display();
};

#endif // CLASSIFICATIONNO_H
