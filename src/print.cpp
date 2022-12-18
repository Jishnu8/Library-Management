#include "include/print.h"
#include "ui_print.h"

Print::Print(QWidget *parent, QString *headers, int size) :
    QMainWindow(parent),
    ui(new Ui::Print)
{
    ui->setupUi(this);
    rowHeaders = new QString[size];
    for (int i = 0; i < size; i++){
        rowHeaders[i] = headers[i];
    }
    rowHeadersSize = size;
}

Print::~Print()
{
    delete ui;
}

void Print::Show(QString message)
{
    updateUI(message);
    show();
}

void Print::updateUI(QString message){
    QSqlQueryModel * model = new QSqlQueryModel(this);

    QSqlQuery query( MyDB::getInstance()->getDBInstance());
    query.prepare(message);

    if(!query.exec())
       qDebug() << query.lastError().text() << query.lastQuery();
    else
       qDebug() << "== success query fetch()";

    model->setQuery(query);
    ui->table->setModel(model);
    ui->table->verticalHeader()->setVisible(false);
    ui->table->horizontalHeader()->setFixedHeight(50);

    for (int i = 0; i < rowHeadersSize; i++){
        ui->table->model()->setHeaderData(i,Qt::Horizontal, rowHeaders[i]);
    }

    ui->table->show();
}
