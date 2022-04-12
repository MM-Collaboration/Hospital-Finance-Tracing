#ifndef CONNECTDATABASEDIALOG_H
#define CONNECTDATABASEDIALOG_H

#include <QDialog>
#include <QSqlDatabase>

namespace Ui {
class ConnectDatabaseDialog;
}

class ConnectDatabaseDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ConnectDatabaseDialog();
    ~ConnectDatabaseDialog();

    struct DatabaseData {
        QString databaseType;
        QString hostName;
        int port;
        QString databaseName;
        QString userName;
        QString password;
    };

    DatabaseData getDatabaseData();

private slots:

private:
    Ui::ConnectDatabaseDialog *ui;
};

#endif // CONNECTDATABASEDIALOG_H
