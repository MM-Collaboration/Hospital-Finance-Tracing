#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSqlTableModel>
#include <QMessageBox>
#include <QSqlError>
<<<<<<< HEAD
=======
#include <QSqlRecord>
#include <QSqlField>
>>>>>>> refs/remotes/origin/mashanew

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    doctorsModel = nullptr;
    patientsModel = nullptr;
    visitsModel = nullptr;
    ui->setupUi(this);
    mDatabase=QSqlDatabase::addDatabase("QMYSQL");
    mDatabase.setHostName("localhost");
    mDatabase.setDatabaseName("hospital");
    mDatabase.setPort(3306);
    mDatabase.setUserName("root");
<<<<<<< HEAD
    mDatabase.setPassword("root");
    if (!mDatabase.open()){
        QMessageBox::critical(this, "Error", mDatabase.lastError().text());
        return;
    }
    mModel=new QSqlTableModel;
    mModel-> setTable("hospital");
    mModel-> select();

    ui-> tableView_visits-> setModel(mModel);
=======
    mDatabase.setPassword("");
    if (!mDatabase.open()){
        QMessageBox::critical(this, "Error", mDatabase.lastError().text());
    }
//    mModel=new QSqlTableModel;
//    mModel-> setTable("doctors");
//    mModel-> select();

//    ui->tableView_doctors->setModel(mModel);
//    loadTableDoctors();

//    ui-> tableView_visits-> setModel(mModel);
    loadTableDoctors();
    loadTablePatients();
    loadTableVisits();
>>>>>>> refs/remotes/origin/mashanew
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::loadTableDoctors() {
    if (doctorsModel == nullptr) {
        doctorsModel = new QSqlTableModel();
    }
    doctorsModel->setTable("doctors");
    doctorsModel->select();
    doctorsModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    doctorsModel->setHeaderData(1, Qt::Horizontal, tr("Имя"));
    doctorsModel->setHeaderData(2, Qt::Horizontal, tr("Специализация"));
    doctorsModel->setHeaderData(3, Qt::Horizontal, tr("Квалификация"));
    ui->tableView_doctors->setModel(doctorsModel);
    ui->tableView_doctors->hideColumn(0);
}

void MainWindow::loadTablePatients() {
    if (patientsModel == nullptr) {
        patientsModel = new QSqlTableModel();
    }
    patientsModel->setTable("patients");
    patientsModel->select();
    patientsModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    patientsModel->setHeaderData(1, Qt::Horizontal, tr("Имя"));
    patientsModel->setHeaderData(2, Qt::Horizontal, tr("Год рождения"));
    ui->tableView_patients->setModel(patientsModel);
    ui->tableView_patients->hideColumn(0);
}

void MainWindow::loadTableVisits() {
    if (visitsModel == nullptr) {
        visitsModel = new QSqlTableModel();
    }
    visitsModel->setTable("visits");
    visitsModel->select();
    visitsModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    visitsModel->setHeaderData(1, Qt::Horizontal, tr("Врач"));
    visitsModel->setHeaderData(2, Qt::Horizontal, tr("Пациент"));
    visitsModel->setHeaderData(3, Qt::Horizontal, tr("Диагноз"));
    visitsModel->setHeaderData(4, Qt::Horizontal, tr("Повторный"));
    visitsModel->setHeaderData(5, Qt::Horizontal, tr("Цена"));
    ui->tableView_visits->setModel(visitsModel);
    ui->tableView_visits->hideColumn(0);
}

// Only for development
// Recommend to add db options to ENV


//void MainWindow::loadDatabase() {
//    if (!db.open()) {
//        QMessageBox::warning(this, "Ошибка открытия базы данных", "Не удалось открыть базу данных");
//    } else {
//        loadTableDoctors();
//        loadTablePatients();
//        loadTableVisits();
//    }
//}

void MainWindow::btnAddDoctorClicked() {
    QMessageBox::warning(this,
                         "Hello",
                         "It`s just a msg!");
}

// Actions
void MainWindow::actionOpenFile() {
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Open Database"),
                                                    QDir::homePath(),
                                                    tr("MariaDB files (*.mwb)"));

    QMessageBox::information(this, "Open database", fileName);
}

void MainWindow::actionAbout() {
    QMessageBox::about(this,
                       "О Hospital Finance Tracing",
                       "<p><b>Hospital Finance Tracing</b> - программа для сбора финансовой статистики поликлиники</p>"
                       "<p>GitHub: <a href='https://github.com/MM-Collaboration/Hospital-Finance-Tracing'>https://github.com/MM-Collaboration/Hospital-Finance-Tracing</a></p>");
}

void MainWindow::on_btn_add_doctor_clicked()
{
<<<<<<< HEAD
    mModel->insertRow(mModel->rowCount());
=======
  //  QSqlRecord record = doctorsModel->record();
    QSqlTableModel model;
    model.setTable("test_model");
//    QModelIndex insertIndex = table->currentIndex();H
//    int row = insertIndex.row() == -1 ? 0 : insertIndex.row();
    doctorsModel->insertRow(doctorsModel->rowCount());
    QSqlRecord rec;
    rec.append(QSqlField("name", QVariant::Char));
    rec.append(QSqlField("specialization", QVariant::Char));
    rec.append(QSqlField("qualification", QVariant::Char));

    qDebug() << "lineEdit_fullNameDoctor: " << ui->lineEdit_fullNameDoctor->text();
     qDebug() << "lineEdit_fullNameDoctor: " << ui->comboBox_specialization->currentText();


    rec.setValue(0, ui->lineEdit_fullNameDoctor->text());
    rec.setValue(1, ui->comboBox_specialization->currentText());
    rec.setValue(2, ui->comboBox_qualification->currentText());

//    record.set("doctors", ui->lineEdit_fullNameDoctor->text());
//    record.setValue(ui->lineEdit_fullNameDoctor->text(), );
 //   record.append(QSqlField("doctors", QVariant::Double));
    model.insertRecord(0, rec);
    doctorsModel->insertRecord(0, rec);
    model.select();
    model.submitAll();
    loadTableDoctors();
>>>>>>> refs/remotes/origin/mashanew
}

