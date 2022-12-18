#include "include/users/searchuser.h"
#include "ui_criticalmsgbox.h"
#include "ui_searchuser.h"

SearchUser::SearchUser(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SearchUser)
{
    ui->setupUi(this);
    ptrEditUser = new EditUser(this);
    ptrMessageBox = new MessageBox();
    ptrMsgBox2 = new CriticalMsgBox();
}

SearchUser::~SearchUser()
{
    delete ui;
    delete ptrMessageBox;
    delete ptrMsgBox2;
}

void SearchUser::Show()
{
    resetLineEditText();
    searchClickEvent();
    this->show();
}

void SearchUser::editClickEvent(){
    QModelIndexList selection = ui->userSearchTable->selectionModel()->selectedRows();
    int row = selection.at(0).row();
    QModelIndex index;
    QString cellData;
    int columnCount = ui->userSearchTable->model()->columnCount();
    QString rowData[columnCount];

    for (int i = 0; i < columnCount; i++){
        index =  ui->userSearchTable->model()->index(row,i);
        cellData = ui->userSearchTable->model()->data(index).toString();
        rowData[i] = cellData;
    }

    ptrEditUser->setLineEditText(rowData[1], rowData[2], rowData[3], rowData[4], rowData[5], rowData[6], rowData[7]);
    ptrEditUser->id = rowData[0];
    ptrEditUser->Show();
}


void SearchUser::setEditClickEvent(bool a){
    if (a == true){
        connect(ui->userSearchTable->verticalHeader(), &QHeaderView::sectionClicked, this, &SearchUser::editClickEvent);
    }
    else{
         disconnect(ui->userSearchTable->verticalHeader(), &QHeaderView::sectionClicked, this, &SearchUser::editClickEvent);
    }
}

void SearchUser::deleteEvent(){
    if(ptrMsgBox2->execute == true){
        QModelIndexList selection = ui->userSearchTable->selectionModel()->selectedRows();
        int row = selection.at(0).row();
        QModelIndex index =  ui->userSearchTable->model()->index(row,0);
        QString accessNo = ui->userSearchTable->model()->data(index).toString();
        bool a = checkIssuedBooksList(accessNo);

        if (a == true){
            QSqlQuery query(MyDB::getInstance()->getDBInstance());
            query.clear();
            query.prepare("delete from users where access_no='" + accessNo + "'");
            if(!query.exec())
            {
                qDebug() << query.lastError().text() << query.lastQuery();
                ptrMessageBox->setText("Failed to Delete Item");
                ptrMessageBox->setTitle("Failure");
                ptrMessageBox->Show();
            }
            else
            {
                if(query.numRowsAffected() > 0)
                {
                    qDebug() <<"read was successful "<< query.lastQuery();
                    ptrMessageBox->setText("Item Deleted Successfully");
                    ptrMessageBox->setTitle("Success");
                    ptrMessageBox->Show();
                    this->close();
                }
                else
                    qDebug() <<"Unable to Delete Item";
            }
        }
        else{
            ptrMessageBox->setText("User has issued a book");
            ptrMessageBox->setTitle("Failure");
            ptrMessageBox->Show();
        }
    }
}

void SearchUser::deleteClickEvent(){
    ptrMsgBox2->setText("Are you sure you want to delete this user?");
    QObject::connect(ptrMsgBox2->ui->okButton,&QPushButton::clicked, this, &SearchUser::deleteEvent);
    ptrMsgBox2->Show();
}

void SearchUser::setDeleteClickEvent(bool a){
    if (a == true){
        connect(ui->userSearchTable->verticalHeader(), &QHeaderView::sectionClicked, this, &SearchUser::deleteClickEvent);
    }
    else{
        disconnect(ui->userSearchTable->verticalHeader(), &QHeaderView::sectionClicked, this, &SearchUser::deleteClickEvent);
    }

    //ALTER TABLE users AUTO_INCREMENT = 1;
}


void SearchUser::verticalHeaderVisibility(bool a){
    ui->userSearchTable->verticalHeader()->setVisible(a);
}

void SearchUser::searchClickEvent(){
    QString accessNo = ui->txtAccessNo->text();
    QString fullName = ui->txtFullName->text();
    QString username = ui->txtUsername->text();
    QString emailId = ui->txtEmailId->text();
    QString command = "select * from users where 1=1";

    if (!accessNo.isEmpty()){
        command.append(" and access_no=" +accessNo+"");
    }
    if (!fullName.isEmpty()){
        command.append(" and name='" + fullName + "'");
    }
    if (!username.isEmpty()){
        command.append(" and username='" + username + "'");
    }
    if (!emailId.isEmpty()){
        command.append(" and email_id='" + emailId + "'");
    }


    QSqlQueryModel * model = new QSqlQueryModel(this);
    QSqlQuery query( MyDB::getInstance()->getDBInstance());
    query.prepare(command);

    if(!query.exec())
       qDebug() << query.lastError().text() << query.lastQuery();
    else
       qDebug() << "== success query fetch()";

    while(query.next())
    qDebug()<<query.value(0).toString();

    model->setQuery(query);
    ui->userSearchTable->horizontalHeader()->setFixedHeight(35);
    ui->userSearchTable->setModel(model);
    ui->userSearchTable->show();
}

void SearchUser::on_searchButton_clicked()
{
    searchClickEvent();
}

void SearchUser::resetLineEditText(){
    ui->txtAccessNo->clear();
    ui->txtFullName->clear();
    ui->txtUsername->clear();
    ui->txtEmailId->clear();
}

bool SearchUser::checkIssuedBooksList(QString userAccessNo){
    QSqlQuery query2(MyDB::getInstance()->getDBInstance());
    query2.clear();
    QString command = "select * from issued_books where user_access_no='" +userAccessNo +"'";
    qDebug() << userAccessNo;

    query2.prepare(command);
    if(!query2.exec())
       qDebug() << query2.lastError().text() << query2.lastQuery();
    else
       qDebug() << "== success query fetch()";

    while(query2.next()){
        if (query2.value(7).isNull() == true){
            return false;
        }
    }

    return true;
}
