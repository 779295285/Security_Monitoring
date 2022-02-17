#ifndef MAIN_REPLAYWIDGET_H
#define MAIN_REPLAYWIDGET_H

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
#include<QStackedWidget>
#include<QListWidget>
#include<QDebug>
#include <QCalendarWidget>
#include <QDateEdit>
#include <QFile>


#include "controller/videocontrol.h"
#include "controller/imagecontrol.h"
#include "model/videomodel.h"
#include "model/imagemodel.h"
#include "play_widget.h"
#include "image_widegt.h"


class Main_ReplayWidget : public QWidget
{
    Q_OBJECT
public:
    explicit Main_ReplayWidget(QWidget *parent = nullptr);
    void init_UI();
    void init_connect();
    void videolist();
    void imagelist();
    void lastvideo_play();


private:
        QWidget *leftWidget,*rightWidget,*rightWidget2,
                *midWidget,*rightBottomWidget,*righttopWidget;
        QVBoxLayout *leftLayout,*rightLayout,
                    *righttopLayout,*midLayout;
        QStackedWidget *StackedWidget;
        QHBoxLayout *rightBottomLayout,*totalLayout,*rightLayout2;

        QPushButton *Inquire_btn,*Next_btn,*Previous_btn,
                     *video_btn,*image_btn;
        QLabel *video_label,*video_label2;

        QImage image;
        QListWidget *playList,*image_List;
        Play_Widget *replayWidget;
        Image_Widegt *ImageWidget;

        QWidget *leftWidget1,*bottomWidget,*rightWidget3,
                *rightWidget4,*topWidget;
        QVBoxLayout *leftLayout1,*rightLayout3;
        QHBoxLayout *rightLayout4,*bottomLayout;
        QGridLayout *topLayout;

        QLabel *name_label,*size_label,*resolution_label;
        Decode_Replay *decodeThread;
        int page;
        QDateEdit *date;
        QString *date_time;

        QImage Image;

        QImage image_size;

signals:

public slots:
        void click_video(QListWidgetItem *item);
        void tovideo();
        void toimage();
        void next();
        void previous();
        void calendar_query();
        void receiveimg(QImage img);
        void click_image(QListWidgetItem *item);
        //void update();

protected:
        void paintEvent(QPaintEvent *);

};

#endif // MAIN_REPLAYWIDGET_H
