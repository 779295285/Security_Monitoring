#include "videocontrol.h"
VideoControl *VideoControl::contorl=nullptr;
VideoControl::VideoControl()
{

}

//外部公共接口 获取control对象
VideoControl *VideoControl::getInstance()
{
    if(VideoControl::contorl=nullptr)
    {
        VideoControl::contorl=new VideoControl();
    }
    return VideoControl::contorl;

}
//从model层添加视频信息
int VideoControl::addVideoPath(QString video_name, QString cover_path, QString video_path)
{
    return VideoModel::getInstance()->addVideoPath(video_name,cover_path,video_path);
}
//从model层获取多个视频路径和视频名称---视频列表显示
char **VideoControl::getVideoPath()
{
    return VideoModel::getInstance()->getVideoPath();
}
//从model层获取指定视频路径---视频播放
char **VideoControl::getVideo(QString name)
{
    return VideoModel::getInstance()->getVideo(name);
}
//从model层日历查询视频信息
char **VideoControl::calendar_query(QString date)
{
    return VideoModel::getInstance()->calendar_query(date);
}

//从model层获取最后一个视频路径
char **VideoControl::getLastvideo()
{
    return VideoModel::getInstance()->getLastvideo();
}
