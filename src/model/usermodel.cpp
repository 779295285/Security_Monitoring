#include "usermodel.h"

UserModel *UserModel::moder =nullptr;

UserModel::UserModel()
{

}
//外部公共接口 获取model对象
UserModel *UserModel::getInstance()
{
    if(UserModel::moder==nullptr)
    {
        UserModel::moder=new UserModel;
    }
    return UserModel::moder;
}
//验证用户和密码
int UserModel::getUserByNamePwd(QString account, QString pwd)
{
    char sql[256];

    char **qres;
    int row,col;
    sprintf(sql,"select * from user where account='%s' AND password='%s';",
            account.toStdString().c_str(),pwd.toStdString().c_str());
    int res = SingelDB::getInstance()->dosql(sql,qres,row,col);
    //res为查询成功
    if(res==0)
    {
        //如果row大于0说明验证成功
        if(row>0)
        {
            return 0;
        }
        //反之说明验证失败
        else
        {
            return 1;
        }
    }
    //查询失败
    else
    {
        return -1;
    }
}


//核对用户是否存在
int UserModel::checkUserByNamePwd(QString account)
{
    char sql[256];
    sprintf(sql,"select * from user where account='%s';",
            account.toStdString().c_str());
    char **qres;
    int row,col;
    int res = SingelDB::getInstance()->dosql(sql,qres,row,col);
    if(res==0)
    {
        //如果row大于0用户存在
        if(row>0)
        {
            return 0;
        }
        //反之说明用户不存在
        else
        {
            return 1;
        }
    }
    //查询失败
    else
    {
        return -1;
    }
}

//添加用户
int UserModel::addUser(QString account,QString user_name, QString pwd)
{
    char sql[256];
    sprintf(sql,"insert into user(account,user_name,password)values('%s','%s','%s');",
            account.toStdString().c_str(),user_name.toStdString().c_str(),pwd.toStdString().c_str());
    char **qres;
    int row,col;
    return SingelDB::getInstance()->dosql(sql,qres,row,col);
}




