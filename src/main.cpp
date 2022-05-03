#include "mainwindow.h"

#include <QApplication>
#include <QtSql>
#include <QSqlTableModel>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow mainWindow;
    mainWindow.show();
    return a.exec();
}
