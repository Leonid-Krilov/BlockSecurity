#ifndef BLUETOOTH_H
#define BLUETOOTH_H

#include "workdatabase.h"
#include "panelenterpasswd.h"

#include <windows.h>
#include <QBluetoothLocalDevice>
#include <QBluetoothDeviceInfo>
#include <QBluetoothDeviceDiscoveryAgent>
#include <QTimer>

class Bluetooth:public QObject{
    Q_OBJECT
public:
    Bluetooth();

public slots:
    void reConnect();
    void blockWorkStation(const QBluetoothDeviceInfo &info);
private:
    int rssi;
    QString address;
    WorkDatabase workDB;
    QBluetoothDeviceDiscoveryAgent *discoveryAgent;
    QTimer *timer;
    PanelEnterPasswd open;
};

#endif // BLUETOOTH_H
