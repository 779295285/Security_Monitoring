#ifndef VIDEOCONTROL_H
#define VIDEOCONTROL_H

#include <QString>
#include "model/videomodel.h"
class VideoControl
{
public:
    //外部公共接口 获取control对象
    static VideoControl *getInstance();
    //从model层添加图片信息
    int addVideoPath(QString video_name, QString cover_path, QString video_path);
    //从model层获取多个视频路径和视频名称---视频列表显示
    char **getVideoPath();
    //从model层获取指定视频路径---视频播放
    char **getVideo(QString name);
    //从model层日历查询视频信息
    char **calendar_query(QString date);
    //从model层获取最后一个视频路径
    char **getLastvideo();
private:
    VideoControl();//构造私有化
    static VideoControl *contorl;//静态私成员变量

};

#endif // VIDEOCONTROL_H
