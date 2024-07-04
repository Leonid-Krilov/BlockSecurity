#include "bluetooth.h"

Bluetooth::Bluetooth():QObject(){
    workDB.outMacPasswd();
    address=workDB.outDB(outMacPassdwDB::MAC);

    timer=new QTimer(this);
    discoveryAgent = new QBluetoothDeviceDiscoveryAgent();

    connect(discoveryAgent, &QBluetoothDeviceDiscoveryAgent::deviceDiscovered, this, &Bluetooth::blockWorkStation);
    connect(discoveryAgent, &QBluetoothDeviceDiscoveryAgent::deviceUpdated, this, &Bluetooth::blockWorkStation);

    connect(timer, &QTimer::timeout, this, &Bluetooth::reConnect);

    discoveryAgent->start();
    timer->start(5000);
}

void Bluetooth::reConnect(){
    discoveryAgent->stop();
    discoveryAgent->start();
}

int token=0;
constexpr int TOKEN=40;
constexpr int CHECKPOINTRSSI=-70;

void Bluetooth::blockWorkStation(const QBluetoothDeviceInfo &info){
    if(info.address().toString()==address){
        token=0;
        rssi=info.rssi();

        if(rssi<CHECKPOINTRSSI){
            LockWorkStation();
            if(!open.isVisible()){
                open.showFullScreen();
                open.setWindowTitle("Panel enter password");
                open.setWindowFlag(Qt::WindowStaysOnTopHint);
                workDB.insertDataLogs(true);
            }
        }
    }else{
        while(info.address().toString()!=address){
            token++;
            if(token==TOKEN && !open.isVisible()){
                token=0;
                open.showFullScreen();
                workDB.insertDataLogs(true);
                open. setWindowTitle("Panel enter password");
                open.setWindowFlag(Qt::WindowStaysOnTopHint);
                LockWorkStation();
            }
            break;
        }
    }
}
