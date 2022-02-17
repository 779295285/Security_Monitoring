#ifndef SETCONTROL_H
#define SETCONTROL_H
#include <QString>
#include "model/setmodel.h"
class SetControl
{
public:
    //外部公共接口 获取control对象
    static SetControl *getInstance();
    //第一次设置参数存储到数据库
    int doSet(QString Video_path,QString Image_path,int framecount,QString cameraName);
    //获取设置信息视频保存路径
    QString getSetting_videopath();
    //获取设置信息图片保存路径
    QString getSetting_imagepath();
    //获取设置信息视频间隔
    int getSetting_interval();
    //获取设置信息，用于判断是否有设置过
    int getSetting();
    //更新设置信息
    int updateSetting(QString Video_path, QString Image_path, int framecount, QString cameraName);
private:
    SetControl();//构造私有化
    static SetControl *contorl;//静态私成员变量
};

#endif // SETCONTROL_H
