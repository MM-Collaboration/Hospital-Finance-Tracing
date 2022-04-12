#include "connectdatabasedialog.h"
#include "ui_connectdatabasedialog.h"

ConnectDatabaseDialog::ConnectDatabaseDialog() :
    QDialog(),
    ui(new Ui::ConnectDatabaseDialog)
{
    ui->setupUi(this);
}

ConnectDatabaseDialog::~ConnectDatabaseDialog()
{
    delete ui;
}

ConnectDatabaseDialog::DatabaseData ConnectDatabaseDialog::getDatabaseData() {
    return ConnectDatabaseDialog::DatabaseData {
                                                ui->comboBox_databaseType->currentText(),
                                                ui->lineEdit_hostName->text(),
                                                ui->lineEdit_port->text().toInt(),
                                                ui->lineEdit_databaseName->text(),
                                                ui->lineEdit_userName->text(),
                                                ui->lineEdit_password->text(),
                                                };
}

//void ConnectDatabaseDialog::getConnectionData() {
//    *hostName = ui->lineEdit_hostName->text();
//    *port = ui->lineEdit_port->text();
//    *databaseName = ui->lineEdit_databaseName->text();
//    *userName = ui->lineEdit_userName->text();
//    *password = ui->lineEdit_password->text();
//}

//void ConnectDatabaseDialog::on_btn_connectDatabase_clicked() {
//    if (!hostName.isEmpty() && !port.isEmpty() && !databaseName.isEmpty() && !userName.isEmpty()) {
//        db = QSqlDatabase::addDatabase("QMYSQL");
//        db.setHostName("localhost");
//        db.setDatabaseName("hospital");
//        db.setPort(3306);
//        db.setUserName("root");
//        db.setPassword("");
//        db.open();
//    }

//}

