#ifndef IMAGE_WIDEGT_H
#define IMAGE_WIDEGT_H

#include <QWidget>
#include <QLabel>
#include <QHBoxLayout>
#include <QString>
#include <QImage>

class Image_Widegt : public QWidget
{
    Q_OBJECT
public:
    //图片放大函数
    explicit Image_Widegt(QString image_path,QWidget *parent = nullptr);
private:
    QLabel *image_label;
    QHBoxLayout *totalLayout;

signals:

public slots:
};

#endif // IMAGE_WIDEGT_H
