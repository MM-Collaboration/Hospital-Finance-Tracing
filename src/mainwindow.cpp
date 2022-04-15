#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->btn_add_doctor, SIGNAL(released()), this, SLOT(btnAddDoctorClicked()));
    // Connect actions
    connect(ui->action_openFile, &QAction::triggered, this, &MainWindow::actionOpenFile);
    // Help menu
    connect(ui->action_about, &QAction::triggered, this, &MainWindow::actionAbout);
    connect(ui->action_aboutQt, &QAction::triggered, this, QApplication::aboutQt);
    connect(ui->action_connectDatabase, &QAction::triggered, this, &MainWindow::createConnectDatabaseDialog);

    connectDatabase();
    // need to connect with QSettings
//    openDatabase();
//    loadDatabase();

}

MainWindow::~MainWindow()
{
    db.close();
    delete ui;
}

void MainWindow::connectDatabase() {
    createConnectDatabaseDialog();
    db.open();
    loadDatabase();
}

void MainWindow::loadTableDoctors() {
    doctorsModel = new QSqlTableModel();
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
    patientsModel = new QSqlTableModel();
    patientsModel->setTable("patients");
    patientsModel->select();
    patientsModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    patientsModel->setHeaderData(1, Qt::Horizontal, tr("Имя"));
    patientsModel->setHeaderData(2, Qt::Horizontal, tr("Год рождения"));
    ui->tableView_patients->setModel(patientsModel);
    ui->tableView_patients->hideColumn(0);
}

void MainWindow::loadTableVisits() {
    visitsModel = new QSqlTableModel();
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
void MainWindow::quickOpenDatabase() {
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("hospital");
    db.setPort(3306);
    db.setUserName("root");
    db.setPassword("");
    db.open();
}

void MainWindow::loadDatabase() {
    if (!db.open()) {
        QMessageBox::warning(this, "Ошибка открытия базы данных", "Не удалось открыть базу данных");
    } else {
        loadTableDoctors();
        loadTablePatients();
        loadTableVisits();
    }
}

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
                       "<p><b>Hospital Finance Tracing</b> - программа для сбора финансовой статистик поликлинники</p>"
                       "<p>GitHub: <a href='https://github.com/MM-Collaboration/Hospital-Finance-Tracing'>https://github.com/MM-Collaboration/Hospital-Finance-Tracing</a></p>");
}

 void MainWindow::createConnectDatabaseDialog() {
    ConnectDatabaseDialog dial;
    dial.setModal(true);
    // Set current db options to dialog
    if (!(db.driverName().isEmpty())) {
        dial.setDBType(db.driverName());
        dial.setHostName(db.hostName());
        dial.setPort(db.port());
        dial.setDatabaseName(db.databaseName());
        dial.setUserName(db.userName());
    }

    // Set db options from dialog
    if (dial.QDialog::exec()) {
        db = QSqlDatabase::addDatabase(dial.getDBType());
        db.setHostName(dial.getHostName());
        db.setPort(dial.getPort());
        db.setDatabaseName(dial.getDatabaseName());
        db.setUserName(dial.getUserName());
        db.setPassword(dial.getPassword());
    }
}
