#include "setcontrol.h"
SetControl *SetControl::contorl=nullptr;
SetControl::SetControl()
{
}

//外部公共接口 获取control对象
SetControl *SetControl::getInstance()
{
    if(SetControl::contorl=nullptr)
    {
        SetControl::contorl=new SetControl();
    }
    return SetControl::contorl;
}

//第一次设置参数存储到数据库
int SetControl::doSet(QString Video_path,QString Image_path,int framecount,QString cameraName)
{
    return SetModel::getInstance()->addSetting(Video_path,Image_path,framecount,cameraName);
}

//获取视频路径
QString SetControl::getSetting_videopath()
{
    QString videopath;
    SetModel::getInstance()->getSetting_videopath(videopath);
    return videopath;
}

//获取设置信息图片路径
QString SetControl::getSetting_imagepath()
{
    QString imagepath;
    SetModel::getInstance()->getSetting_imagepath(imagepath);
    return imagepath;
}

//获取视频录制时长
int SetControl::getSetting_interval()
{

    return SetModel::getInstance()->getSetting_interval();
}

//获取设置信息，用于判断是否有设置过
int SetControl::getSetting()
{
    return SetModel::getInstance()->getSetting();
}

//更新设置信息
int SetControl::updateSetting(QString Video_path, QString Image_path, int framecount, QString cameraName)
{
    return SetModel::getInstance()->updateSetting(Video_path,Image_path,framecount,cameraName);
}


