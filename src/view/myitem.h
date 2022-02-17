#ifndef MYITEM_H
#define MYITEM_H

#include <QObject>
#include<QGraphicsItem>
#include<QString>
#include<QRectF>
#include<QPainter>
#include<QStyleOptionGraphicsItem>
#include<QWidget>
#include<QPixmap>
#include<QPainter>
#include <synchapi.h>

class MyItem:public QObject,public QGraphicsItem
{
    Q_OBJECT
public:
    MyItem(QString path,int move);
    //返回图元绘制的矩阵区域
    QRectF boundingRect() const;
    //绘制图元内容
    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget);
    void advance(int);

    int status;
private:
    QString itempath;
    QPixmap img;
    int move;
signals:
    void end();

};

#endif // MYITEM_H
