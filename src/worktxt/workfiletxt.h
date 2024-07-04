#ifndef WORKFILETXT_H
#define WORKFILETXT_H

#include <QFile>
#include <QDir>

enum returnData:int{
    URL,
    PORT,
    NAMEDB,
    USER,
    PASSWD
};

class WorkFileTxt
{
public:
    WorkFileTxt();
    QString returnLine(returnData type);

    void writeInfoDB(QString url, QString port, QString nameDB, QString nameUser, QString passwd);
    int outInfoDB();

    void autorunWrite(bool point);
    int autorunOut();
private:
    QString line[5];
};

#endif // WORKFILETXT_H
