#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "workfiletxt.h"
#include "workdatabase.h"
#include <QMainWindow>
#include <QLineEdit>
#include <QPushButton>
#include <QCloseEvent>
#include <QCheckBox>
#include <QShortcut>

#include <QIcon>
#include <QSystemTrayIcon>
#include <QMenu>

QT_BEGIN_NAMESPACE
namespace Ui{
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
protected:
    void closeEvent(QCloseEvent *eventClose) override;
public slots:
    void showWindow();
    void saveInfo();
private:
    bool connected;
    QShortcut *key;
    Ui::MainWindow *ui;
    QLineEdit *lineUrl, *linePort, *lineNameDB,
        *lineUserName, *linePasswd, *lineRezultConnect;
    QPushButton *buttonSave, *buttonExit;
    WorkFileTxt workTxt;
    QCheckBox checkBoxAutorun;
    WorkDatabase workDB;

    QSystemTrayIcon *trayIcon;
    QMenu *trayMenu;
    QAction *openWindow, *quitAction;
};
#endif // MAINWINDOW_H
