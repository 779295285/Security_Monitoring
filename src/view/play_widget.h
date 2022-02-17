#ifndef PLAY_WIDGET_H
#define PLAY_WIDGET_H
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPaintEvent>
#include<QComboBox>
#include<QImage>
#include<QPixmap>
#include "ffmpeg/decode_replay.h"
#include "ffmpeg/ftrancetomp4.h"
#include<QMessageBox>
class Play_Widget : public QWidget
{
    Q_OBJECT
public:
    explicit Play_Widget(QString PATH,QWidget *parent = nullptr);
    void init_UI();
    void init_control();
    void init_connect();
    Decode_Replay *decodeThread;
     static QString path;

private:
    QVBoxLayout *totalLayout;
    QWidget *bottomWidget,*topWidget;
    QHBoxLayout *bottomLayout,*topLayout;
    QLabel *video_label;
    QPushButton *play_btn,*screenshots_btn,*export_btn;
    QComboBox *Timesthespeed_box;
    QImage Image;
    FTranceTomp4 *trance;
    int mark;

signals:

public slots:
    void receiveimg(QImage img);
    void continue_stop();
    void screenshots();
    void trancetomp4();
protected:
        void paintEvent(QPaintEvent *);
};

#endif // PLAY_WIDGET_H
