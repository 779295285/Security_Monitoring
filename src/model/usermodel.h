#ifndef USERMODEL_H
#define USERMODEL_H
#include <QString>
#include <QDebug>
#include "singeldb.h"
#include <iostream>
using namespace std;

class UserModel
{
public:
    //外部公共接口 获取model对象
    static UserModel *getInstance();
    //验证用户和密码
    int getUserByNamePwd(QString account,QString pwd);
    //添加用户
    int addUser(QString account,QString user_name,QString pwd);
    //核对用户是否存在
    int checkUserByNamePwd(QString account);

private:
    UserModel();    //构造私有化
    static UserModel *moder; //静态私成员变量
    sqlite3 *sqldb;
    char *errmsg;  //用来存储错误信息字符串
};

#endif // USERMODEL_H
