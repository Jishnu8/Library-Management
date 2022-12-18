#ifndef MESSAGEBOX_H
#define MESSAGEBOX_H

#include <QMainWindow>
#include <QPixmap>

namespace Ui {
class MessageBox;
}

class MessageBox : public QMainWindow
{
    Q_OBJECT

public:
    explicit MessageBox(QWidget *parent = nullptr);
    ~MessageBox();
    void Show();
    void setText(QString);
    void setTitle(QString);

private slots:
    void on_okButton_clicked();

private:
    Ui::MessageBox *ui;
};

#endif // MESSAGEBOX_H
