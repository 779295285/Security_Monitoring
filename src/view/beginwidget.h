#ifndef BEGINWIDGET_H
#define BEGINWIDGET_H
#include <QBrush>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QIcon>
#include "view/myitem.h" //自己定义的图元类
#include <QPixmap>
#include<QTimer>
#include "view/main_widget.h"
#include "view/setwidget.h"
#include "controller/setcontrol.h"

class BeginWidget:public QGraphicsView
{
    Q_OBJECT
public:
    BeginWidget();


    Main_Widget *Main;
    SetWidget *setting;
    QGraphicsScene *scene;
    MyItem *item1,*item2;
    QTimer *timer;
    void init_UI();
    void init_control();
    void init_connect();
public slots:
    void watchStatus();
    void toSettingorMainWidget();


};

#endif // BEGINWIDGET_H
