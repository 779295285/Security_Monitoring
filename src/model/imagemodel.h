#ifndef IMAGEMODEL_H
#define IMAGEMODEL_H
#include "singeldb.h"
#include <iostream>
#include <QString>

class ImageModel
{
public:
    //外部公共接口 获取model对象
    static ImageModel *getInstance();
    //添加设置信息
    int addImagePath(QString video_name, QString cover_path);
    //获取多个图片路径 9个为一组
    char **getImagePath(int num);
    //获取图片路径
    char **getimage(QString name);

    static int row , col;
private:
    ImageModel();//构造私有化
    static ImageModel *moder; //静态私成员变量
    sqlite3 *sqldb;
    char *errmsg;  //用来存储错误信息字符串
};

#endif // IMAGEMODEL_H
