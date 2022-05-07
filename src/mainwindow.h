#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "connectdatabasedialog.h"

#include <QMainWindow>
#include <QMessageBox>
#include <QPushButton>
#include <QSqlTableModel>
#include <QSqlRelationalTableModel>
#include <QSqlDatabase>
#include <QDebug>
#include <QFileDialog>
#include <QRegExpValidator>
#include <QStandardItem>
#include <QSqlQuery>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    bool createConnection();
    void loadDatabase();
    void reloadTableDoctors();
    void reloadTablePatients();
    void reloadTableVisits();

    void doctorsSubmit();

protected:

private slots:
    // Actions
    void actionOpenFile();
    void actionAbout();

//    void submit();

    void on_btn_add_patient_clicked();

    void on_btn_edit_patient_clicked();

    void on_btn_add_doctor_clicked();

    void on_lineEdit_fullNameDoctor_textChanged();

    void on_lineEdit_fullNamePatient_textChanged();

private:
    Ui::MainWindow *ui;

    QPushButton *btnStat;
    QPushButton *btnAddDoctor;
    QSqlTableModel *doctorsModel;
    QSqlTableModel *patientsModel;
    QSqlRelationalTableModel *visitsModel;
    QSqlDatabase db;

    // Regular expresions
    QRegExp *fullNameRegExp;
};
#endif // MAINWINDOW_H
