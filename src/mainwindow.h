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
#include <QStringListModel>

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
    void loadDoctorsSpecializationComboBox();
    void loadDoctorsQualificationComboBox();

    void doctorsSubmit();
    void updateStatDoctorsCheckBox();

    void activatePatientAddPushButton();
    void activateVisitAddPushButton();

    void updateStatAllList(QStringList &);
    
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

    void on_btn_add_appointment_clicked();

    void on_tableView_patients_clicked(const QModelIndex &index);

    void on_tableView_doctors_clicked(const QModelIndex &index);

    void on_tableView_visits_clicked(const QModelIndex &index);

    void on_pushButton_statUpdate_clicked();

    void on_lineEdit_phoneNumberPatient_textChanged(const QString &arg1);

    void on_lineEdit_visitDiagnosis_textChanged(const QString &arg1);

private:
    Ui::MainWindow *ui;

    QPushButton *btnStat;
    QPushButton *btnAddDoctor;
    int *statModelIndex = 0;
    QStringListModel *statListModel;
    QModelIndex *statModel;
    QSqlTableModel *doctorsModel;
    QSqlTableModel *patientsModel;
    QSqlRelationalTableModel *visitsModel;
    QSqlDatabase db;

    double *statPriceList;

    // Regular expresions
    QRegExp *fullNameRegExp;
};
#endif // MAINWINDOW_H
