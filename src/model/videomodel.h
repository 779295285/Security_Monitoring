#ifndef VIDEOMODEL_H
#define VIDEOMODEL_H
#include "singeldb.h"
#include <iostream>
#include <QString>

class VideoModel
{
public:
    //外部公共接口 获取model对象
    static VideoModel *getInstance();
    //添加图片信息
    int addVideoPath(QString video_name, QString cover_path, QString video_path);
    //获取多个视频路径和视频名称---视频列表显示
    char **getVideoPath();
    //获取指定视频路径---视频播放
    char **getVideo(QString name);
    //日历查询视频信息
    char **calendar_query(QString date);
    //获取最后一个视频路径
    char **getLastvideo();
    static int row,col;
private:
    VideoModel();//构造私有化
    static VideoModel *moder; //静态私成员变量
    sqlite3 *sqldb;
    char *errmsg;  //用来存储错误信息字符串
};

#endif // VIDEOMODEL_H
