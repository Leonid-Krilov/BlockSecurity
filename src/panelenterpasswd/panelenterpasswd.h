#ifndef PANELENTERPASSWD_H
#define PANELENTERPASSWD_H

#include "workfiletxt.h"
#include "workdatabase.h"

#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QTextEdit>
#include <QTimer>
#include <QVBoxLayout>
#include <QScreen>
#include <QRect>

namespace Ui{
class PanelEnterPasswd;
}

class PanelEnterPasswd : public QWidget{
    Q_OBJECT

public:
    explicit PanelEnterPasswd(QWidget *parent = nullptr);
    ~PanelEnterPasswd();
public slots:
    void resultEnterPasswd();
private:
    Ui::PanelEnterPasswd *ui;
    QString passwdUser;
    QLineEdit *lineEnterPasswd;
    QPushButton *buttonEnterPasswd;
    QTimer *timer;
    WorkFileTxt *workTxt;
    WorkDatabase enter;
};

#endif // PANELENTERPASSWD_H
