#include "imagecontrol.h"
ImageControl *ImageControl::contorl=nullptr;
ImageControl::ImageControl()
{


}

//外部公共接口 获取control对象
ImageControl *ImageControl::getInstance()
{
    if(ImageControl::contorl=nullptr)
    {
        ImageControl::contorl=new ImageControl();
    }
    return ImageControl::contorl;
}

//从control层添加图片路径到数据库----截图
int ImageControl::addImagePath(QString video_name, QString cover_path)
{
    return ImageModel::getInstance()->addImagePath(video_name,cover_path);
}

//从control层获取数据库中的图片路径----照片列表
char **ImageControl::getImagePath(int num)
{
    return ImageModel::getInstance()->getImagePath(num);
}

//从control层获取数据库中的图片路径-----照片放大
char **ImageControl::getimage(QString name)
{
    return ImageModel::getInstance()->getimage(name);
}
