#ifndef ERROR_H
#define ERROR_H

#include <QMessageBox>
#include <QPushButton>
#include <QProcess>
#include <QCoreApplication>
#include <QApplication>

class Error:public QObject{
public:
    Error();

    void searchUser();
    void connected();
};

#endif // ERROR_H
