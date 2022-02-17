#ifndef IMAGECONTROL_H
#define IMAGECONTROL_H
#include <QString>
#include "model/imagemodel.h"
class ImageControl
{
public:
    //外部公共接口 获取control对象
    static ImageControl *getInstance();
    //从control层添加图片路径到数据库----截图
    int addImagePath(QString video_name, QString cover_path);
    //从control层获取数据库中的图片路径----照片列表
    char **getImagePath(int num);
    //从control层获取数据库中的图片路径----照片放大
    char **getimage(QString name);
private:
    ImageControl();//构造私有化
    static ImageControl *contorl;//静态私成员变量
};

#endif // IMAGECONTROL_H
