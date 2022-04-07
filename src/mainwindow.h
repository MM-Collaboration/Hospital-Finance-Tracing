#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QPushButton>
#include <QSqlTableModel>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:

private slots:
    void btnAddDoctorClicked();

    // Actions
    void actionOpenFile();
    void actionAbout();

private:
    Ui::MainWindow *ui;

    QPushButton *btnStat;
    QPushButton *btnAddDoctor;
};
#endif // MAINWINDOW_H
