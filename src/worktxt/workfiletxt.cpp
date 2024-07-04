#include "workfiletxt.h"

WorkFileTxt::WorkFileTxt(){}

QString WorkFileTxt::returnLine(returnData type){
    return line[type];
}

void WorkFileTxt::writeInfoDB(QString url, QString port, QString nameDB, QString nameUser, QString passwd){
    const QString PATH="../data/DATA";
    QFile file(PATH);
    QTextStream write(&file);

    if (file.open(QIODevice::WriteOnly | QIODevice::Text)){
        write<<url<<"\n";
        write<<port<<"\n";
        write<<nameDB<<"\n";
        write<<nameUser<<"\n";
        write<<passwd<<"\n";

        file.close();
    }
}

constexpr int ELAF = 5;

int WorkFileTxt::outInfoDB(){
    const QString PATH="../data/DATA";

    QFile file(PATH);
    QTextStream out(&file);

    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)){}

    if(file.size()==0)
        return 1;
    else{
        for(int i=0;i<ELAF;i++){
            this->line[i]=out.readLine();
        }
    }

    file.close();

    return 0;
}

void WorkFileTxt::autorunWrite(bool point){
    const QString PATH="../data/AUTORUN";

    QFile file(PATH);
    QTextStream write(&file);

    if (file.open(QIODevice::WriteOnly | QIODevice::Text)){
        if(point)
            write<<1;
        else
            write<<0;
    }
}

int WorkFileTxt::autorunOut(){
    const QString PATH="../data/AUTORUN";
    int intPoint=0;
    QFile file(PATH);
    QTextStream out(&file);

    if (file.open(QIODevice::ReadOnly | QIODevice::Text)){
        QString stringPoint=out.readLine();
        file.close();

        intPoint=stringPoint.toInt();
    }
    return intPoint;
}
