#include "main_monitorwidget.h"

Main_MonitorWidget::Main_MonitorWidget(QWidget *parent) : QWidget(parent)
{
    init_control();
    init_connect();
}
//监控界面控件布局
void Main_MonitorWidget::init_control()
{
    this->totalLayout = new QHBoxLayout();
    this->leftLayout = new QVBoxLayout();
    this->rightLayout = new QVBoxLayout();
    this->leftWidget =new QWidget();
    this->rightWidget =new QWidget();
    this->rightBottomWidget =new QWidget();
    this->righttopWidget =new QWidget();
    this->rightBottomLayout=new QHBoxLayout();
    this->righttopLayout = new QGridLayout();
    this->leftWidget->setStyleSheet("background:gray");

    QListWidget *playList = new QListWidget;
    //设置QListWidget的显示模式
    playList-> setViewMode (QListView::IconMode) ;
    //设置QListWidget中单元项的间距
    playList-> setSpacing(0) ;
    //设置自动适应布局调整(Adjust适应， Fixed不适应)，默认不适应
    playList-> setResizeMode (QListWidget::Adjust);
    //设置不能移动
    playList-> setMovement (QListWidget::Static) ;
    playList->setStyleSheet("border:none;font-size:15px");

    camera = Decode::getcamera();
    for(int i = 0;i<camera.size();i++)
    {
        //定义QListWidgetItem对象
        QListWidgetItem *playItem = new QListWidgetItem ;
        //为单元项设置属性
        //设置文
        playItem->setTextColor("white");
        playItem->setText(camera.at(i));
        //重新设置单元项图片的宽度和高度
        playItem->setSizeHint(QSize(200,50));
        //将单元项添加到QListWidget中
        playList->addItem(playItem);
        this->leftLayout->addWidget(playList);
    }

    this->leftWidget->setLayout(leftLayout);

    //右上
    this->video1_label = new QLabel(this);
    this->video1_label->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    this->video1_label->setMinimumSize(100,30);
    //label显示画面控件初始化
    this->video2_label = new QLabel(this);
    this->video2_label->setStyleSheet("background:gray");
    this->video3_label = new QLabel(this);
    this->video3_label->setStyleSheet("background:gray");
    this->video4_label = new QLabel(this);
    this->video4_label->setStyleSheet("background: gray");
    //添加到布局，田字格布局
    this->righttopLayout->addWidget(video1_label,0,0);
    this->righttopLayout->addWidget(video2_label,0,1);
    this->righttopLayout->addWidget(video3_label,1,0);
    this->righttopLayout->addWidget(video4_label,1,1);

    this->righttopLayout->setRowStretch(0,1);
    this->righttopLayout->setRowStretch(1,1);
    this->righttopLayout->setColumnStretch(0,1);
    this->righttopLayout->setColumnStretch(1,1);
    this->righttopWidget->setLayout(righttopLayout);


    //右下
    this->single_screen_btn = new QPushButton("单",this);
    this->multi_screen_btn = new QPushButton("双",this);
    this->rightBottomLayout->addWidget(single_screen_btn);
    this->rightBottomLayout->addWidget(multi_screen_btn);
    this->rightBottomLayout->addStretch(0);
    this->rightBottomWidget->setLayout(rightBottomLayout);


    //右边布局
    this->rightLayout->addWidget(righttopWidget,95);
    this->rightLayout->addWidget(rightBottomWidget,5);
    this->rightWidget->setLayout(rightLayout);

    this->totalLayout ->setSpacing(0);
    this->totalLayout->setMargin(0);
    this->totalLayout->addWidget(leftWidget,17);
    this->totalLayout->addWidget(rightWidget,83);
    this->setLayout(totalLayout);
}

//连接函数
void Main_MonitorWidget::init_connect()
{
    connect(this->single_screen_btn,SIGNAL(clicked()),this,SLOT(ToSingle()));
    connect(this->multi_screen_btn,SIGNAL(clicked()),this,SLOT(ToFour()));
}

//实时显示监控画面解码函数
void Main_MonitorWidget::startdecode()
{
    this->decodeThread =new Decode();
    decodeThread->start();
    connect(decodeThread,SIGNAL(sendImg(QImage)),this,SLOT(receiveImg(QImage)));
}

//接收图片函数
void Main_MonitorWidget::receiveImg(QImage img)
{
    this->image =img;
    this->update();
}

//监控界面label控件接收图片事件
void Main_MonitorWidget::paintEvent(QPaintEvent *)
{
    //如果这个图片不为空
    if(!this->image.isNull())
    {
        //显示在label上
        QPixmap *image = new QPixmap(QPixmap::fromImage(this->image));
        image->scaled(video1_label->size(),Qt::KeepAspectRatio);
        video1_label->setPixmap(QPixmap::fromImage(this->image));
        video1_label->setScaledContents(true);
    }
}

//切换单画面模式
void Main_MonitorWidget::ToSingle()
{

    this->righttopLayout->removeWidget(video2_label);
    this->righttopLayout->removeWidget(video3_label);
    this->righttopLayout->removeWidget(video4_label);
    this->video2_label->setVisible(false);
    this->video3_label->setVisible(false);
    this->video4_label->setVisible(false);

    this->video1_label->setMinimumSize(1109,703);
}

//切换多画面模式
void Main_MonitorWidget::ToFour()
{

    this->video1_label->setMinimumSize(100,30);
    this->righttopLayout->addWidget(video2_label);
    this->righttopLayout->addWidget(video3_label);
    this->righttopLayout->addWidget(video4_label);
    this->video2_label->setVisible(true);
    this->video3_label->setVisible(true);
    this->video4_label->setVisible(true);
    this->righttopLayout->addWidget(video1_label,0,0);
    this->righttopLayout->addWidget(video2_label,0,1);
    this->righttopLayout->addWidget(video3_label,1,0);
    this->righttopLayout->addWidget(video4_label,1,1);

    this->righttopLayout->setRowStretch(0,1);
    this->righttopLayout->setRowStretch(1,1);
    this->righttopLayout->setColumnStretch(0,1);
    this->righttopLayout->setColumnStretch(1,1);
}


