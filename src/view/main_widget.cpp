#include "main_widget.h"
int Main_Widget::status=0;
//主界面构造函数
Main_Widget::Main_Widget(QWidget *parent) : QWidget(parent)
{
    init_UI();
    init_control();
    init_connect();
}
//主界面窗口设置
void Main_Widget::init_UI()
{
    this->setWindowTitle("主界面");
    this->setFixedSize(1400,900);
    this->totalLayout = new QVBoxLayout();

}
//主界面布局
void Main_Widget::init_control()
{
    //上布局
    this->topLayout = new QHBoxLayout();
    this->topWidget = new QWidget(this);
    this->topWidget->setStyleSheet("background:gray");
    //下布局
    this->bottomWidget = new QStackedWidget(this);
    this->bottomWidget->setStyleSheet("background:white");

    this->play_btn = new QPushButton("监控模式",this);
    this->play_btn->setFixedSize(100,60);

    this->replay_btn = new QPushButton("回放模式",this);
    this->replay_btn->setFixedSize(100,60);

    this->log_btn = new QPushButton("日志查询",this);
    this->log_btn->setFixedSize(100,60);

    this->setting_btn = new QPushButton("系统设置",this);
    this->setting_btn->setFixedSize(100,60);

    //定时器--刷新时间
    this->time_label =new QLabel(this);
    this->timer = new QTimer(this);
    timer->start(500);

    //new一个监控模式布局
    this->monitor = new Main_MonitorWidget();
    //开始解码显示监控画面
    monitor->startdecode();
    //将监控模式布局放到堆栈布局里面
    this->bottomWidget->addWidget(monitor);

    //new一个回放模式布局
    this->replay = new Main_ReplayWidget();
    //将回放模式布局放到堆栈布局里面
    this->bottomWidget->addWidget(replay);
    //设置当前布局为监控模式
    this->bottomWidget->setCurrentWidget(monitor);

    //顶部导航栏布局
    this->topLayout->addStretch(0);
    this->topLayout->setSpacing(18);
    this->topLayout->addWidget(this->play_btn);
    this->topLayout->addWidget(this->replay_btn);
    this->topLayout->addWidget(this->log_btn);
    this->topLayout->addWidget(this->setting_btn);
    this->topLayout->addWidget(this->time_label);
    this->topWidget->setLayout(topLayout);

    this->totalLayout->addWidget(topWidget,1);
    this->totalLayout->addWidget(bottomWidget,9);
    this->setLayout(totalLayout);
}
//连接函数
void Main_Widget::init_connect()
{
    connect(timer, SIGNAL(timeout()), this, SLOT(qtimeSlot()));
    connect(setting_btn, SIGNAL(clicked()), this, SLOT(Tosetting()));
    connect(replay_btn, SIGNAL(clicked()), this, SLOT(Toreplay()));
    connect(play_btn, SIGNAL(clicked()), this, SLOT(Tomonitor()));
}

//获取当前时间函数
void Main_Widget::qtimeSlot()
{
    QDateTime date_time =QDateTime::currentDateTime();
    QString current_date =date_time.toString(" yyyy.MM.dd \nhh:mm:ss ddd");
    this->time_label->setText (current_date);
}

//跳转到设置窗口函数
void Main_Widget::Tosetting()
{
    //如果没有登录过显示登录窗口
    if(this->status==0)
    {
        this->loginwidget = new loginWidget;
        this->loginwidget->show();
    }
    else
    {
        this->setting = new SetWidget();
        this->setting->show();
    }



}

//跳转到回放模式函数
void Main_Widget::Toreplay()
{
    //如果没有登录过显示登录窗口
    if(this->status==0)
    {
        this->loginwidget = new loginWidget;
        this->loginwidget->show();
    }
    else
    {
        this->replay->videolist();
        //this->replay->lastvideo_play();
        this->replay->init_connect();
        this->bottomWidget->setCurrentWidget(replay);
    }

}

//跳转到监控模式函数
void Main_Widget::Tomonitor()
{
    //如果没有登录过显示登录窗口
    if(this->status==0)
    {
        this->loginwidget = new loginWidget;
        this->loginwidget->show();
    }
    else
    {
        this->bottomWidget->setCurrentWidget(monitor);
    }


}

//关闭设置窗口函数
void Main_Widget::Tomain()
{
    this->setting->close();
}
