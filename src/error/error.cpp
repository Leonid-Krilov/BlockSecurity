#include "error.h"

Error::Error(){}

void Error::searchUser(){
    QMessageBox errorDialog;
    errorDialog.setIcon(QMessageBox::Critical);
    errorDialog.setWindowFlags(Qt::Window | Qt::CustomizeWindowHint | Qt::WindowTitleHint);

    errorDialog.setText("Произошла ошибка с поиском пользователя. Сообщите администратору! Нажмите кнопку 'Перезагрузка', чтобы перезагрузить приложение.");
    errorDialog.setWindowTitle("Ошибка");

    QPushButton *reloadButton = errorDialog.addButton("Перезагрузка", QMessageBox::ActionRole);

    QObject::connect(reloadButton, &QPushButton::clicked, this,[](){
        QProcess process;

        process.startDetached("BlockSecurity.exe",QStringList());

        exit(0);
    });

    errorDialog.exec();
}

void Error::connected(){
    QMessageBox errorDialog;
    errorDialog.setIcon(QMessageBox::Critical);
    errorDialog.setWindowFlags(Qt::Window | Qt::CustomizeWindowHint | Qt::WindowTitleHint);

    errorDialog.setText("Произошла ошибка с подключением к БД. Сообщите администратору! Нажмите кнопку 'Перезагрузка', чтобы перезагрузить приложение.");
    errorDialog.setWindowTitle("Ошибка");

    // Создаем кнопку "Перезагрузка"
    QPushButton *reloadButton = errorDialog.addButton("Перезагрузка", QMessageBox::AcceptRole);

    // Подключаем сигнал нажатия кнопки к слоту обработки
    QObject::connect(reloadButton, &QPushButton::clicked, this,[](){
        QProcess process;

        process.startDetached("BlockSecurity.exe",QStringList());

        exit(0);
    });

    // Показываем диалоговое окно
    errorDialog.exec();
}
