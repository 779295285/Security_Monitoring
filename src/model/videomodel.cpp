#include "videomodel.h"
VideoModel *VideoModel::moder =nullptr;
int VideoModel::row=0;
int VideoModel::col=0;
VideoModel::VideoModel()
{

}

//外部公共接口 获取model对象
VideoModel *VideoModel::getInstance()
{
    if(VideoModel::moder==nullptr)
    {
        VideoModel::moder=new VideoModel;
    }

    return VideoModel::moder;
}
//添加视频信息
int VideoModel::addVideoPath(QString video_name, QString cover_path, QString video_path)
{
    char sql[256];
    sprintf(sql,"insert into video(video_name,cover_path,video_path)values('%s','%s','%s');",
            video_name.toStdString().c_str(),cover_path.toStdString().c_str(),video_path.toStdString().c_str());
    char **qres;
    int row,col;
    return SingelDB::getInstance()->dosql(sql,qres,row,col);
}
//获取多个视频路径和视频名称---视频列表显示
char **VideoModel::getVideoPath()
{
    char sql[256];
    sprintf(sql,"select video_name,cover_path from video;");
    char **qres;
    //int row,col;
    SingelDB::getInstance()->dosql(sql,qres,row,col);
    return qres;
}

//获取指定视频路径---视频播放
char **VideoModel::getVideo(QString name)
{
    char sql[256];
    sprintf(sql,"select video_path from video where video_name = '%s' ;",name.toStdString().c_str());
    char **qres;
    int row,col;
    SingelDB::getInstance()->dosql(sql,qres,row,col);
    return qres;
}

//日历查询视频信息
char **VideoModel::calendar_query(QString date)
{
    char sql[256];
    sprintf(sql,"select video_name,cover_path from video where video_name like '%s%';",date.toStdString().c_str());
    char **qres;
    //int row,col;
    SingelDB::getInstance()->dosql(sql,qres,row,col);
    return qres;
}

//获取最后一个视频路径
char **VideoModel::getLastvideo()
{
    char sql[256];
    sprintf(sql,"select video_path from video order by video_id desc limit 1;");
    char **qres;
    int row,col;
    SingelDB::getInstance()->dosql(sql,qres,row,col);
    return qres;

}


