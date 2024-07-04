#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include<QMessageBox>
#include "workfiletxt.h"
#include "autorun.h"

MainWindow::MainWindow(QWidget *parent):QMainWindow(parent),ui(new Ui::MainWindow){
    trayIcon = new QSystemTrayIcon(QIcon("../data/icon/key.png"));

    // Создаем контекстное меню для tray icon
    trayMenu = new QMenu();
    openWindow = new QAction("Открыть окно настроек", this);
    quitAction = new QAction("Выход", qApp);

    connect(quitAction, &QAction::triggered, qApp, &QApplication::quit);
    connect(openWindow, &QAction::triggered, this, &MainWindow::showWindow);

    trayMenu->addAction(openWindow);
    trayMenu->addAction(quitAction);

    trayIcon->setContextMenu(trayMenu);
    trayIcon->show();

    ui->setupUi(this);

    this->setWindowIcon(QIcon("../data/icon/key.png"));

    this->setWindowTitle("Block Security");
    this->setWindowModality(Qt::ApplicationModal);
    this->setFixedSize(356, 475);

    lineUrl=new QLineEdit;
    linePort=new QLineEdit;
    lineNameDB=new QLineEdit;
    lineUserName=new QLineEdit;
    linePasswd=new QLineEdit;

    ui->linePasswd->setEchoMode(QLineEdit::Password);

    lineRezultConnect=new QLineEdit;
    ui->lineRezultConnect->setReadOnly(true);

    if(workTxt.autorunOut()==1)
        ui->checkBoxAutorun->setChecked(true);
    else
        ui->checkBoxAutorun->setChecked(false);

    if(workTxt.outInfoDB()==1){
        ui->lineUrl->setPlaceholderText("Enter URL");
        ui->linePort->setPlaceholderText("Enter Port");
        ui->lineNameDB->setPlaceholderText("Enter Name Database");
        ui->lineUserName->setPlaceholderText("Enter Username");
        ui->linePasswd->setPlaceholderText("Enter Password");
    }else{
        ui->lineUrl->setPlaceholderText(workTxt.returnLine(returnData::URL));
        ui->linePort->setPlaceholderText(workTxt.returnLine(returnData::PORT));
        ui->lineNameDB->setPlaceholderText(workTxt.returnLine(returnData::NAMEDB));
        ui->lineUserName->setPlaceholderText(workTxt.returnLine(returnData::USER));
        ui->linePasswd->setPlaceholderText("**************");
    }

    connect(ui->buttonSave, &QPushButton::clicked, this, &MainWindow::saveInfo);
}

MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::showWindow(){
    show();
}

void MainWindow::closeEvent(QCloseEvent *eventClose){
    eventClose->ignore();
    hide();
}

void MainWindow::saveInfo(){
    QString url=ui->lineUrl->text();
    QString port=ui->linePort->text();
    QString nameDB=ui->lineNameDB->text();
    QString userName=ui->lineUserName->text();
    QString passwd=ui->linePasswd->text();
    Autorun autorun;

    if(workTxt.outInfoDB()==0 && (url.isEmpty()||port.isEmpty()||nameDB.isEmpty()||userName.isEmpty()||passwd.isEmpty())){
        ui->lineRezultConnect->setStyleSheet("background-color: green;");
        ui->lineRezultConnect->setText("Saved setting autorun!");

        if(ui->checkBoxAutorun->checkState()){
            workTxt.autorunWrite(true);
            autorun.start();
        }
        else{
            workTxt.autorunWrite(false);
            autorun.stop();
        }
    }else{
        if(!workDB.checkConnectedDatabase(url,port,nameDB,userName,passwd)){
            ui->lineRezultConnect->setStyleSheet("background-color: red;");
            ui->lineRezultConnect->setText("Not connected! Not Saved!");
        }else{
            ui->lineRezultConnect->setStyleSheet("background-color: green;");
            workTxt.writeInfoDB(url,port,nameDB,userName,passwd);

            if(ui->checkBoxAutorun->checkState()){
                workTxt.autorunWrite(true);
                autorun.start();
            }
            else{
                workTxt.autorunWrite(false);
                autorun.stop();
            }

            ui->lineRezultConnect->setText("Connected! Saved!");
        }
    }
}
