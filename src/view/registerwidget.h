#ifndef REGISTERWIDGET_H
#define REGISTERWIDGET_H
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QDialog>
#include <QPainter>
#include <QMessageBox>
#include <QKeyEvent>
#include <QRegExpValidator>
#include <QCryptographicHash>

#include "controller/usercontrol.h"
class RegisterWidget : public QWidget
{
    Q_OBJECT
public:
    explicit RegisterWidget(QWidget *parent = nullptr);
    void keyPressEvent(QKeyEvent *event);
    void init_UI();
    void init_control();
    void init_connect();
    int mark;

public slots:
    //点击注册按钮是执行的槽函数
    void regist();
    void PlainAndCipher();
    QString GetMd5(const QString &value);

private:
   QLabel *account_label,*user_label,*password_label,
          *password_label2;

   QPushButton *register_btn,*qsc_btn,*eye_btn;
   QLineEdit *account_edit,*user_edit,*password_edit,
             *password_edit2;


signals:
   void back();

};

#endif // REGISTERWIDGET_H
