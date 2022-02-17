#ifndef LOGINWIDGET_H
#define LOGINWIDGET_H
#include "controller/setcontrol.h"
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QTime>
#include <QDialog>
#include <QPainter>
#include <QIcon>
#include <QMessageBox>
#include<QDebug>
#include <QPaintEvent>
#include <QCryptographicHash>

#include "controller/usercontrol.h"
#include "view/registerwidget.h"
class loginWidget : public QWidget
{
    Q_OBJECT
public:
    loginWidget(QWidget *parent = 0);
    void paintEvent(QPaintEvent *event);
    void init_UI();
    void init_control();
    void init_connect();
    QString getcode();
    void mousePressEvent(QMouseEvent *event);
    ~loginWidget();
    int mark;

public slots:
    void login();//点击登录按钮是执行的槽函数
    void toreg();
    void backlog();
    void PlainAndCipher();
    QString GetMd5(const QString &value);


private:
    QLabel *user_label,*password_label,*code_label;
    QPushButton *login_btn,*qsc_btn,*register_btn,*eye_btn;
    QLineEdit *user_edit,*password_edit,*Vericode_edit;
    QString code;
    RegisterWidget *regWin;
};

#endif // LOGINWIDGET_H
