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
    delete ui;
}

