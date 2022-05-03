#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QMainWindow>
#include <QMessageBox>
#include <QPushButton>
#include <QSqlTableModel>
#include <QSqlDatabase>
#include <QDebug>
#include <QFileDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class QSqlTableModel;
class QSqlError;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void loadDatabase();

    void loadTableDoctors();

    void loadTablePatients();

    void loadTableVisits();



protected:

private slots:
    void btnAddDoctorClicked();
    // Actions
    void actionOpenFile();
    void actionAbout();

    void on_btn_add_doctor_clicked();

private:
    Ui::MainWindow *ui;

    QPushButton *btnStat;
    QPushButton *btnAddDoctor;
    QSqlTableModel *doctorsModel;
    QSqlTableModel *patientsModel;
    QSqlTableModel *visitsModel;
    QSqlTableModel *mModel;
    QSqlDatabase mDatabase;

};
#endif // MAINWINDOW_H
