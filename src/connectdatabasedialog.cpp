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
