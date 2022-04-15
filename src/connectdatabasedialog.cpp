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

QString ConnectDatabaseDialog::getDBType() {
    return ConnectDatabaseDialog::ui->comboBox_databaseType->currentText();
}

QString ConnectDatabaseDialog::getHostName() {
    return ConnectDatabaseDialog::ui->lineEdit_hostName->text();
}

int ConnectDatabaseDialog::getPort() {
    return ConnectDatabaseDialog::ui->lineEdit_port->text().toInt();
}

QString ConnectDatabaseDialog::getDatabaseName() {
    return ConnectDatabaseDialog::ui->lineEdit_databaseName->text();
}

QString ConnectDatabaseDialog::getUserName() {
    return ConnectDatabaseDialog::ui->lineEdit_userName->text();
}

QString ConnectDatabaseDialog::getPassword() {
    return ConnectDatabaseDialog::ui->lineEdit_password->text();
}

void ConnectDatabaseDialog::setDBType(QString type) {
    int comboBoxIndex = ui->comboBox_databaseType->findText(type);
    if (comboBoxIndex != -1){
        ui->comboBox_databaseType->setCurrentIndex(comboBoxIndex);
    }
}

void ConnectDatabaseDialog::setHostName(QString hostName) {
    ui->lineEdit_hostName->setText(hostName);
}

void ConnectDatabaseDialog::setDatabaseName(QString databaseName) {
    ui->lineEdit_databaseName->setText(databaseName);
}

void ConnectDatabaseDialog::setPort(int port) {
    ui->lineEdit_port->setText(QString().number(port));
}

void ConnectDatabaseDialog::setUserName(QString username) {
    ui->lineEdit_userName->setText(username);
}

void ConnectDatabaseDialog::setPassword(QString password) {
    ui->lineEdit_password->setText(password);
}
