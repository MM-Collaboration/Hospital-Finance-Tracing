#ifndef CONNECTDATABASEDIALOG_H
#define CONNECTDATABASEDIALOG_H

#include <QDialog>

namespace Ui {
class ConnectDatabaseDialog;
}

class ConnectDatabaseDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ConnectDatabaseDialog();
    ~ConnectDatabaseDialog();

    QString getDBType();
    QString getHostName();
    int getPort();
    QString getDatabaseName();
    QString getUserName();
    QString getPassword();

    void setDBType(QString type);
    void setHostName(QString hostName);
    void setDatabaseName(QString databaseName);
    void setPort(int port);
    void setUserName(QString username);
    void setPassword(QString password);


private slots:

private:
    Ui::ConnectDatabaseDialog *ui;
};

#endif // CONNECTDATABASEDIALOG_H
