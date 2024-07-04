#include "mainwindow.h"
#include "bluetooth.h"
#include "workdatabase.h"

#include <QApplication>

int main(int argc, char *argv[]){
    QApplication a(argc, argv);

    WorkDatabase data;
    data.connected();
    data.outMacPasswd();

    Bluetooth bluetooth;
    MainWindow mainWindow;

    return a.exec();
}
