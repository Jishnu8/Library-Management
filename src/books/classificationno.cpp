#include "include/books/classificationno.h"
#include "ui_classificationno.h"

ClassificationNo::ClassificationNo(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ClassificationNo)
{
    ui->setupUi(this);
    display();
}

ClassificationNo::~ClassificationNo()
{
    delete ui;
}

void ClassificationNo::display(){
    QString command = "select * from classification_numbers";
    QSqlQueryModel * model = new QSqlQueryModel(this);
    QSqlQuery query( MyDB::getInstance()->getDBInstance());
    query.prepare(command);

    if(!query.exec())
       qDebug() << query.lastError().text() << query.lastQuery();
    else
       qDebug() << "== success query fetch()";

    model->setQuery(query);
    ui->classificationNoTable->setModel(model);
    ui->classificationNoTable->verticalHeader()->setVisible(false);
    ui->classificationNoTable->show();
}

void ClassificationNo::Show(){
    this->show();
}
