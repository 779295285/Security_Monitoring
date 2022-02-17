#ifndef SETMODEL_H
#define SETMODEL_H
#include "singeldb.h"
#include <iostream>
#include <QString>
#include <qDebug>
class SetModel
{
public:
    //外部公共接口 获取model对象
    static SetModel *getInstance();
    //添加设置信息
    int addSetting(QString Video_path,QString Image_path,int framecount,QString cameraName);
    //更新设置信息
    int updateSetting(QString Video_path,QString Image_path,int framecount,QString cameraName);
    //获取设置信息
    int getSetting();
    //获取设置信息视频保存路径
    void getSetting_videopath(QString &videopath);
    //获取设置信息图片保存路径
    void getSetting_imagepath(QString &imagpath);
    //获取设置信息视频间隔
    int getSetting_interval();
private:
    SetModel();//构造私有化
    static SetModel *moder; //静态私成员变量
    sqlite3 *sqldb;
    char *errmsg;  //用来存储错误信息字符串
};

#endif // SETMODEL_H
