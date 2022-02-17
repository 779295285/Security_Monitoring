#ifndef USERCONTROL_H
#define USERCONTROL_H
#include <QString>
#include "model/usermodel.h"
class UserControl
{
public:
    //外部公共接口 获取control对象
    static UserControl *getInstance();
    //登录验证
    int doLogin(QString account,QString pwd);
    //注册
    int doReister(QString account,QString user_name, QString pwd);
private:
    UserControl();//构造私有化
    static UserControl *contorl;//静态私成员变量
};

#endif // USERCONTROL_H
