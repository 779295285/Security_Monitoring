#include "imagemodel.h"
ImageModel *ImageModel::moder =nullptr;
int ImageModel::row=0;
int ImageModel::col=0;
ImageModel::ImageModel()
{

}
//外部公共接口 获取model对象
ImageModel *ImageModel::getInstance()
{
    if(ImageModel::moder==nullptr)
    {
        ImageModel::moder=new ImageModel;
    }
    return ImageModel::moder;
}
//添加设置信息
int ImageModel::addImagePath(QString video_name, QString cover_path)
{
    char sql[256];
    sprintf(sql,"insert into image(image_name,image_path)values('%s','%s');",
            video_name.toStdString().c_str(),cover_path.toStdString().c_str());
    char **qres;
    int row,col;
    return SingelDB::getInstance()->dosql(sql,qres,row,col);
}
//获取多个图片路径 9个为一组
char **ImageModel::getImagePath(int num)
{
    char sql[256];
    sprintf(sql,"select image_path,image_name from image limit 9 offset (%d-1)*9;",num);
    char **qres;
    //int row,col;
    SingelDB::getInstance()->dosql(sql,qres,row,col);
    return qres;
}

//获取图片路径
char **ImageModel::getimage(QString name)
{
    char sql[256];
    sprintf(sql,"select image_path from image where image_name = '%s';",name.toStdString().c_str());
    char **qres;
    int row,col;
    SingelDB::getInstance()->dosql(sql,qres,row,col);
    return qres;
}


