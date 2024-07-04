#include "workdatabase.h"
#include "workfiletxt.h"


WorkDatabase::WorkDatabase(){}

QString WorkDatabase::outDB(outMacPassdwDB out){
    return outArray[out];
}

void WorkDatabase::connected(){
    WorkFileTxt read;
    read.outInfoDB();
    if(read.outInfoDB()==1){
        while(read.outInfoDB()!=1)
            break;
    }else{
        QSqlDatabase db=QSqlDatabase::addDatabase("QMYSQL");
        db.setHostName(read.returnLine(returnData::URL));
        db.setPort(read.returnLine(returnData::PORT).toInt());
        db.setDatabaseName(read.returnLine(returnData::NAMEDB));
        db.setUserName(read.returnLine(returnData::USER));
        db.setPassword(read.returnLine(returnData::PASSWD));

        if(!db.open()){
            error.connected();
            checkConnected=false;
        }
        else{
            checkConnected=true;
        }
    }
}

bool WorkDatabase::checkConnectedDatabase(QString url, QString port, QString namDB, QString userName, QString passwd){
    QSqlDatabase db=QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName(url);
    db.setPort(port.toInt());
    db.setDatabaseName(namDB);
    db.setUserName(userName);
    db.setPassword(passwd);

    if(!db.open())
        return false;
    else{
        db.close();
        return true;
    }
}

void WorkDatabase::insertDataLogs(bool check){
    QSqlQuery query;
    QString textValue;

    query.prepare("INSERT INTO `Logs` (`id`, `Name PC`, `Time`, `Text`) VALUES (NULL, :hostName, NOW(), :text)");
    QString hostName=QHostInfo::localHostName();
    query.bindValue(":hostName", hostName);

    if(check){
        textValue="Computer block!";
        query.bindValue(":text", textValue);
    }else{
        textValue="Computer unblock!";
        query.bindValue(":text", textValue);
    }
    query.exec();
}

void WorkDatabase::attemptLogin(){
    QSqlQuery query;
    QString textValue;

    query.prepare("INSERT INTO `Logs` (`id`, `Name PC`, `Time`, `Text`) VALUES (NULL, :hostName, NOW(), :text)");
    QString hostName=QHostInfo::localHostName();
    query.bindValue(":hostName", hostName);
    textValue="Login attempt";
    query.bindValue(":text", textValue);

    query.exec();
}

void WorkDatabase::outMacPasswd(){
    QSqlQuery query;
    QString macAddress, passwd;
    query.prepare("SELECT * FROM `user_mac` WHERE NameUser = :hostName" );

    QString hostName=QHostInfo::localHostName();
    query.bindValue(":hostName", hostName);

    if (query.exec()){
        if(query.size()==0){
            error.searchUser();
        }
        while (query.next()) {
            macAddress = query.value("MAC").toString();
            passwd=query.value("Passwd").toString();

            outArray.append(macAddress);
            outArray.append(passwd);
        }
    }
}
