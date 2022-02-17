#include "image_widegt.h"

//图片放大构造函数
Image_Widegt::Image_Widegt(QString image_path,QWidget *parent) : QWidget(parent)
{
    this->setWindowTitle("播放界面");
    this->setFixedSize(640,481);
    this->totalLayout = new QHBoxLayout();

    this->image_label = new QLabel();
    QImage *image = new QImage(image_path);
    this->image_label->setPixmap(QPixmap::fromImage(*image));
    this->image_label->setScaledContents(true);
    this->totalLayout->addWidget(image_label);
    this->setLayout(totalLayout);
}


