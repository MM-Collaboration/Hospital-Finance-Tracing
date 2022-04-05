#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->btn_add_doctor, SIGNAL(released()), this, SLOT(btnAddDoctorClicked()));
    connect(ui->action_openFile, &QAction::triggered, this, &MainWindow::actionOpenFile);
}

void MainWindow::btnAddDoctorClicked() {
    QMessageBox::warning(this, "Hello", "It`s just a msg!");
}

// Actions
void MainWindow::actionOpenFile() {
    QMessageBox::information(this, "Hey!", "You have triggered actionOpneFile");
}
MainWindow::~MainWindow()
{
    delete ui;
}

