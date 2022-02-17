#include "usercontrol.h"
UserControl *UserControl::contorl=nullptr;
//外部公共接口 获取control对象
UserControl *UserControl::getInstance()
{
    if(UserControl::contorl=nullptr)
    {
        UserControl::contorl=new UserControl();
    }
    return UserControl::contorl;
}
//登录验证，0表示验证成功，1表示验证失败
int UserControl::doLogin(QString account, QString pwd)
{
    return UserModel::getInstance()->getUserByNamePwd(account,pwd);
}

//注册
int UserControl::doReister(QString account,QString user_name, QString pwd)
{
    int res=UserModel::getInstance()->checkUserByNamePwd(account);
    //res为0说明用户存在
    if(res==1)
    {
        return UserModel::getInstance()->addUser(account,user_name,pwd);
    }
    //res为1说明用户不存在
    else
    {
        return -1;
    }
}

UserControl::UserControl()
{

}
