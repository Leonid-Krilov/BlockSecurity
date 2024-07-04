#include "panelenterpasswd.h"
#include "ui_panelenterpasswd.h"

PanelEnterPasswd::PanelEnterPasswd(QWidget *parent):QWidget(parent), ui(new Ui::PanelEnterPasswd){
    enter.outMacPasswd();
    passwdUser=enter.outDB(outMacPassdwDB::PASSWDUSER);

    setWindowModality(Qt::ApplicationModal);
    setWindowFlags(Qt::FramelessWindowHint);
    setWindowFlags(Qt::Window | Qt::CustomizeWindowHint | Qt::WindowTitleHint);

    QScreen *screen = QGuiApplication::primaryScreen();
    QRect screenGeometry = screen->geometry();
    int height = screenGeometry.height();
    int width = screenGeometry.width();

    // Установка фиксированного размера окна
    setFixedSize(width, height);

    // Отключение кнопок изменения размера и сворачивания окна
    setWindowFlags(Qt::Window | Qt::FramelessWindowHint);

    ui->setupUi(this);
    activateWindow();

    lineEnterPasswd=new QLineEdit();
    ui->lineEnterPasswd->setPlaceholderText("Enter password");
    ui->lineEnterPasswd->setFocus();
    lineEnterPasswd->setEchoMode(QLineEdit::Password);

    buttonEnterPasswd=new QPushButton();

    QHBoxLayout *layout = new QHBoxLayout();
    layout->addStretch();
    layout->addWidget(ui->lineEnterPasswd);
    layout->addWidget(ui->buttonEnterPasswd);
    layout->addStretch();
    setLayout(layout);

    connect(ui->buttonEnterPasswd, &QPushButton::clicked, this, &PanelEnterPasswd::resultEnterPasswd);
    connect(ui->lineEnterPasswd, &QLineEdit::returnPressed, this,  &PanelEnterPasswd::resultEnterPasswd);
}

PanelEnterPasswd::~PanelEnterPasswd(){
    delete ui;
}

int tokenCheck=4;

void PanelEnterPasswd::resultEnterPasswd(){
    QString enterPasswd=ui->lineEnterPasswd->text();

    if(enterPasswd.isEmpty()){
        ui->lineEnterPasswd->setPlaceholderText("The passwd has'nt been entered");
    }else{
        if(enterPasswd==passwdUser){
            ui->lineEnterPasswd->clear();
            this->hide();
            tokenCheck=4;
            ui->lineEnterPasswd->setPlaceholderText("Enter password");
            enter.insertDataLogs(false);
        }else{
            if(tokenCheck!=1){
                QString stringToken=QString::number(tokenCheck-1);
                ui->lineEnterPasswd->clear();
                ui->lineEnterPasswd->setPlaceholderText("The passwd is incorected! There are still attempts left: "+stringToken);
                tokenCheck--;
            }else{
                ui->lineEnterPasswd->clear();
                ui->lineEnterPasswd->setPlaceholderText("Unauthorized access attempt");//попытка НСД
                enter.attemptLogin();
            }
        }    
    }
}
