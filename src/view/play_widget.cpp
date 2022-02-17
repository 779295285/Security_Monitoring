#include "play_widget.h"
QString Play_Widget::path=nullptr;
//播放界面构造函数
Play_Widget::Play_Widget(QString PATH,QWidget *parent) : QWidget(parent)
{
    //mark为暂停标记，1表示继续播放，0 表示暂停
    this->mark = 1;
    init_UI();
    init_control();
    //path为视频路径
    this->path=PATH;
    //创建一个解码线程
    this->decodeThread=new Decode_Replay(path);
    this->decodeThread->start();
    init_connect();
}

//播放界面参数设置
void Play_Widget::init_UI()
{
    this->setWindowTitle("播放界面");
    this->setFixedSize(900,675);
    this->totalLayout = new QVBoxLayout();

}
//播放界面控件布局
void Play_Widget::init_control()
{
    this->bottomWidget=new QWidget();
    this->topWidget=new QWidget();
    this->bottomLayout=new QHBoxLayout();
    this->topLayout=new QHBoxLayout();
    this->video_label=new QLabel();
    this->play_btn=new QPushButton("暂停/播放",this);
    this->screenshots_btn=new QPushButton("截图",this);
    this->export_btn=new QPushButton("导出",this);

    this->Timesthespeed_box = new QComboBox(this);
    this->Timesthespeed_box->clear();
    this->Timesthespeed_box->addItem("1X");
    this->Timesthespeed_box->addItem("0.5X");
    this->Timesthespeed_box->addItem("1.5X");
    this->Timesthespeed_box->addItem("2X");

    this->video_label->setStyleSheet("background:green");

    this->video_label->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    this->video_label->setMinimumSize(850,638);
    this->topLayout->addWidget(video_label);
    this->topWidget->setLayout(topLayout);

    this->bottomLayout->addWidget(play_btn);
    this->bottomLayout->addStretch(0);
    this->bottomLayout->addWidget(Timesthespeed_box);
    this->bottomLayout->addWidget(screenshots_btn);
    this->bottomLayout->addWidget(export_btn);


    this->bottomWidget->setLayout(bottomLayout);

    this->totalLayout->addWidget(topWidget,9);
    this->totalLayout->addWidget(bottomWidget,1);
    this->setLayout(totalLayout);
}

void Play_Widget::init_connect()
{
    connect(Timesthespeed_box,SIGNAL(activated(QString)),decodeThread,SLOT(setSpeed(QString)));
    connect(play_btn, SIGNAL(clicked()), this, SLOT(continue_stop()));
    connect(decodeThread, SIGNAL(sendImg2(QImage)), this, SLOT(receiveimg(QImage)));
    connect(screenshots_btn, SIGNAL(clicked()), this, SLOT(screenshots()));
    connect(export_btn, SIGNAL(clicked()), this, SLOT(trancetomp4()));
}

//接收图片槽函数
void Play_Widget::receiveimg(QImage img)
{
    this->Image =img;
    this->update();
}

//视频暂停函数
void Play_Widget::continue_stop()
{
    //如果标记为0，视频就开始
    if(this->mark==0)
    {
        decodeThread->status=0;
        this->mark=1;
    }
     //如果标记为1，视频就暂停
    else if(this->mark==1)
    {
        decodeThread->status=1;
        this->mark=0;
    }
}

//截图函数
void Play_Widget::screenshots()
{
    decodeThread->screenshots_mark=1;
    QMessageBox::warning(this, tr("提示！"),tr("截图成功！"),QMessageBox::Yes);
}

//转码导出视频函数
void Play_Widget::trancetomp4()
{
    //创建一个解码对象
    this->trance=new FTranceTomp4();
    //将视频路径传到解码
    this->trance->openH264File(path);
    this->trance->coverTomp4();
    QMessageBox::warning(this, tr("提示！"),tr("导出成功！"),QMessageBox::Yes);
}

//监控界面label控件接收图片事件
void Play_Widget::paintEvent(QPaintEvent *)
{
    if(!this->Image.isNull())
    {
        QPixmap *image = new QPixmap(QPixmap::fromImage(this->Image));
        image->scaled(video_label->size(),Qt::KeepAspectRatio);
        video_label->setPixmap(QPixmap::fromImage(this->Image));
        video_label->setScaledContents(true);
    }
}



