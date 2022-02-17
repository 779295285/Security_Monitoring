#include "setmodel.h"

SetModel *SetModel::moder =nullptr;

SetModel::SetModel(){}

//外部公共接口 获取model对象
SetModel *SetModel::getInstance()
{
    if(SetModel::moder==nullptr)
    {
        SetModel::moder=new SetModel;
    }

    return SetModel::moder;
}

//添加设置信息
int SetModel::addSetting(QString Video_path, QString Image_path, int framecount, QString cameraName)
{
    char sql[256];
    sprintf(sql,"insert into setting(video_path,image_path,interval,camera_name)values('%s','%s','%d','%s');",
            Video_path.toStdString().c_str(),Image_path.toStdString().c_str(),
            framecount,cameraName.toStdString().c_str());
    char **qres;
    int row,col;
    return SingelDB::getInstance()->dosql(sql,qres,row,col);
}

//更新设置信息
//返回值0代表更新成功，1代表失败
int SetModel::updateSetting(QString Video_path, QString Image_path, int framecount, QString cameraName)
{
    char sql[256];
    char **qres;
    int row,col;
    sprintf(sql,"update setting set video_path='%s',image_path='%s',interval='%d',camera_name='%s' where set_id=1;",
            Video_path.toStdString().c_str(),Image_path.toStdString().c_str(),framecount,cameraName.toStdString().c_str());
    return SingelDB::getInstance()->dosql(sql,qres,row,col);

}

//获取设置信息
//0表示dosql没有数据，大于0 表示有数据，-1执行失败
int SetModel::getSetting()
{
    char sql[256] = "select * from setting";
    char **qres;
    int col,row;
    int res = SingelDB::getInstance()->dosql(sql,qres,row,col);
    if(res == 0)
    {
        return row;
    }
    return -1;
}

//获取设置信息视频保存路径
void SetModel::getSetting_videopath(QString &videopath)
{
    char sql[256] = "select video_path from setting where set_id=1;";
    char **qres;
    int col,row;
    //将sql语句换成sqlite3可以识别的语句，返回指针到stmt
    int res = SingelDB::getInstance()->dosql(sql,qres,row,col);
    if(res == SQLITE_OK)
    {
        if(row==0)
        {
            return;//没有数据
        }
        //videopath= qres[1];
        videopath = QString(QLatin1String(qres[1]));
    }
}

//获取设置信息图片保存路径
void SetModel::getSetting_imagepath(QString &imagepath)
{
    char sql[256] = "select image_path from setting where set_id=1;";
    char **qres;
    int col,row;
    int res = SingelDB::getInstance()->dosql(sql,qres,row,col);
    if(res == SQLITE_OK)
    {
        if(row==0)
        {           
            return;//没有数据
        }

        imagepath = QString(QLatin1String(qres[1]));
    }
}

int SetModel::getSetting_interval()
{
    char sql[256] = "select interval from setting where set_id=1;";
    char **qres;
    int col,row;
    int res = SingelDB::getInstance()->dosql(sql,qres,row,col);
    if(res == SQLITE_OK)
    {
        if(row==0)
        {
            return 1;//没有数据
        }
        return atoi(qres[1]);
    }
    return -1;
}
