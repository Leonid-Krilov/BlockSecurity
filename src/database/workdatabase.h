#ifndef CONNECT_H
#define CONNECT_H

#include "error.h"

#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QCoreApplication>
#include <QHostInfo>
#include <QString>
#include <QVector>

enum outMacPassdwDB:int{
    MAC,
    PASSWDUSER
};

class WorkDatabase{
public:
    WorkDatabase();

    QString outDB(outMacPassdwDB out);

    void connected();
    void insertDataLogs(bool check);
    void attemptLogin();
    bool checkConnectedDatabase(QString url, QString port, QString namDB, QString userName, QString passwd);
    void outMacPasswd();
private:
    int port;
    bool checkConnected;
    QVector<QString> outArray;
    Error error;
};

#endif // CONNECT_H
