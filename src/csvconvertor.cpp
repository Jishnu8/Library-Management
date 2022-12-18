#include "include/csvconvertor.h"
#include "ui_csvconvertor.h"

CsvConvertor::CsvConvertor(QWidget *parent, QString message,  QString *headers, int size) :
    QMainWindow(parent),
    ui(new Ui::CsvConvertor)
{
    ui->setupUi(this);
    sqlQuery = message;
    rowHeaders = new QString[size];
    for (int i = 0; i < size; i++){
        rowHeaders[i] = headers[i];
    }
    rowHeadersSize = size;
}

CsvConvertor::~CsvConvertor()
{
    delete ui;
}

QString CsvConvertor::getFilePath(){
    QString hash = "/";
    QString path = ui->txtPath->text() + hash + ui->txtFileName->text() + ".csv";
    return path;
}

void CsvConvertor::Show(){
    this->show();
}

void CsvConvertor::sqlToCsv(){
    QSqlQueryModel * model = new QSqlQueryModel();
    QSqlQuery query(MyDB::getInstance()->getDBInstance());
    query.prepare(sqlQuery);

    if(!query.exec()){
       qDebug() << query.lastError().text() << query.lastQuery();
        ptrMessageBox->setText("Failed to save file");
        ptrMessageBox->setTitle("Failed");
        ptrMessageBox->Show();
    }
    else
       qDebug() << "== success query fetch()";

    model->setQuery(query);
    int columnCount = model->columnCount();

    QString path = getFilePath();
    std::ofstream fout(path.toStdString());

    for (int i = 0; i < rowHeadersSize; i++){
        fout << rowHeaders[i].toStdString() << ", ";
    }
    fout << "\n";

    while(query.next()){
        for (int i = 0; i < columnCount; i++){
            fout << query.value(i).toString().toStdString() << ", ";
        }
        fout << "\n";
    }

    ptrMessageBox->setText("File saved successfully");
    ptrMessageBox->setTitle("Success");
    ptrMessageBox->Show();
    this->close();
}


void CsvConvertor::on_cancelButton_clicked()
{
    this->close();
}


void CsvConvertor::on_saveButton_clicked()
{
    sqlToCsv();
}

