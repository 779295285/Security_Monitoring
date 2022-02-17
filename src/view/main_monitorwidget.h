#ifndef MAIN_MONITORWIDGET_H
#define MAIN_MONITORWIDGET_H
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include<QGridLayout>
#include <QPaintEvent>
#include<QList>
#include<QImage>
#include<QPixmap>
#include "ffmpeg/decode.h"

#include<QListWidgetItem>
class Main_MonitorWidget : public QWidget
{
    Q_OBJECT
public:
    explicit Main_MonitorWidget(QWidget *parent = nullptr);

    void init_control();
    void init_control2();
    void init_connect();
    void startdecode();
    Decode *decodeThread;//声明解码线程

private:
        QWidget *rightWidget,*leftWidget,*rightBottomWidget,*righttopWidget;
        QVBoxLayout *leftLayout,*rightLayout;
        QHBoxLayout *rightBottomLayout,*totalLayout;
        QGridLayout *righttopLayout;
        QPushButton *single_screen_btn,*multi_screen_btn;
        QLabel *video1_label,*video2_label,*video3_label,*video4_label;
        QList <QString> camera;
        QImage image;

signals:

public slots:
        void receiveImg(QImage img);
        void ToSingle();
        void ToFour();
protected:
        void paintEvent(QPaintEvent *);
};

#endif // MAIN_MONITORWIDGET_H
