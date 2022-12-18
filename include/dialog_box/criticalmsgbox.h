#ifndef CRITICALMSGBOX_H
#define CRITICALMSGBOX_H

#include <QMainWindow>

namespace Ui {
class CriticalMsgBox;
}

class CriticalMsgBox : public QMainWindow
{
    Q_OBJECT

public:
    Ui::CriticalMsgBox *ui;
    explicit CriticalMsgBox(QWidget *parent = nullptr);
    ~CriticalMsgBox();
    void Show();
    void setText(QString);
    bool execute;
    bool waiting;

private slots:
    void on_cancelButton_clicked();
    void on_okButton_clicked();

private:

};

#endif // CRITICALMSGBOX_H
