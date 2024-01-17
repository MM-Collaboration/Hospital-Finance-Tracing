#ifndef MAINWINDOW_H
#define MAINWINDOW_H

//#include "connectdatabasedialog.h"
#include "statchart.h"

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
#include <QPieSeries>
#include <QBarSet>
#include <QPointF>
#include <QDate>

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
    void reloadTableDoctors();
    void reloadTablePatients();
    void reloadTableVisits();
    void loadDoctorsSpecializationComboBox();
    void loadDoctorsQualificationComboBox();

    void activatePatientAddPushButton();
    void activateVisitAddPushButton();
    
    void updateStatDoctorsCheckBox();
    void updateStatPatientsCheckBox();

    void updateDoctorStat();

    void updateLastPatientsVisits();

    void updateLatestVisitsStat();

    void updatePatientVisitsStat();

    void highlightWidget(QWidget *, bool);

    void activateDoctorAddPushButton();

    double getDoctorPaymentSummary(int doctorId);
    int getSpecializationId(const QString &specialization);
    int getQualificationId(const QString &qualification);
protected:

private slots:
    // Actions
    void actionOpenFile();
    void actionAbout();

    void on_btn_add_patient_clicked();

    void on_btn_add_doctor_clicked();

    void on_lineEdit_fullNameDoctor_textChanged();

    void on_btn_add_appointment_clicked();

    void on_tableView_patients_clicked(const QModelIndex &index);

    void on_tableView_doctors_clicked(const QModelIndex &index);

    void on_tableView_visits_clicked(const QModelIndex &index);

    void on_pushButton_statUpdate_clicked();

    void on_lineEdit_phoneNumberPatient_textChanged(const QString &arg1);

    void on_lineEdit_visitDiagnosis_textChanged(const QString &arg1);

    void on_lineEdit_snils_textChanged(const QString &arg1);

    void on_comboBox_vistPatient_editTextChanged(const QString &arg1);

    void on_comboBox_vistDoctor_editTextChanged(const QString &arg1);

    void on_lineEdit_fullNamePatient_textChanged(const QString &arg1);

    void on_comboBox_doctorSpecialization_currentTextChanged(const QString &arg1);

    void on_comboBox_doctorQualification_currentTextChanged(const QString &arg1);

    private:
    Ui::MainWindow *ui;
    StatChart *m_doctorDonatStatChart;
    StatChart *m_doctorBarStatChart;
    StatChart *m_doctorLineStatChart;

    StatChart *m_patientDonatStatChart;
    StatChart *m_patientBarStatChart;
    StatChart *m_patientLineStatChart;

    QPushButton *btnStat;
    QPushButton *btnAddDoctor;
    QStringListModel *statListModel;
    QSqlTableModel *doctorsModel;
    QSqlTableModel *patientsModel;
    QSqlRelationalTableModel *visitsModel;
    QSqlDatabase db;

    // Regular expresions
    QRegExp *fullNameRegExp;
};
#endif // MAINWINDOW_H
