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

    openDatabase();
    if (!db.open()) {
        QMessageBox::warning(this, "Ошибка открытия базы данных", "Не удалось открыть базу данных");
    } else {
        loadTableDoctors();
        loadTablePatients();
        loadTableVisits();
    }
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

void MainWindow::openDatabase() {
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("hospital");
    db.setPort(3306);
    db.setUserName("root");
    db.setPassword("");
    db.open();
}

void MainWindow::btnAddDoctorClicked() {
    QMessageBox::warning(this,
                         "Hello",
                         "It`s just a msg!");
}

// Actions
void MainWindow::actionOpenFile() {
    QMessageBox::information(this,
                             "Hey!",
                             "You have triggered actionOpneFile");
}

void MainWindow::actionAbout() {
    QMessageBox::about(this,
                       "О Hospital Finance Tracing",
                       "<p><b>Hospital Finance Tracing</b> - программа для сбора финансовой статистик поликлинники</p>"
                       "<p>GitHub: <a href='https://github.com/MM-Collaboration/Hospital-Finance-Tracing'>https://github.com/MM-Collaboration/Hospital-Finance-Tracing</a></p>");
}

// Events

MainWindow::~MainWindow()
{
    db.close();
    delete ui;
}

