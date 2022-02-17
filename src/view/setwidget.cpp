#include "setwidget.h"
#include "main_widget.h"
SetWidget::SetWidget()
{
    this->mark=0;
    init_UI();
    init_control();
    init_connect();
}

void SetWidget::init_UI()
{
    //设置窗口标题
    this->setWindowTitle("安防监控系统");
    //设置窗口大小
    this->setFixedSize(600,400);
}

//设置窗口控件布局函数
void SetWidget::init_control()
{
    /*字体大小  ft1：标题字体大小
              ft2：标签字体大小*/
    QFont ft1,ft2;
    ft1.setPointSize(30);
    ft2.setPointSize(12);

    this->Set_label = new QLabel("设置界面",this);
    this->Set_label->setGeometry(200,30,160,40);
    this->Set_label->setFont(ft1);

    this->VideoPath_label = new QLabel("视频存储位置",this);
    this->VideoPath_label->setGeometry(130,100,80,30);
    this->VideoPath_label->setFont(ft2);

    this->ImagePath_label = new QLabel("图片存储位置",this);
    this->ImagePath_label->setGeometry(130,150,80,30);
    this->ImagePath_label->setFont(ft2);

    this->Interval_label = new QLabel("采集时间间隔",this);
    this->Interval_label->setGeometry(130,200,80,30);
    this->Interval_label->setFont(ft2);

    this->Camera_label = new QLabel("摄像头配置",this);
    this->Camera_label->setGeometry(130,250,80,30);
    this->Camera_label->setFont(ft2);

    this->VideoPath_edit = new QLineEdit(this);
    this->VideoPath_edit->setReadOnly(true);
    this->VideoPath_edit->setGeometry(220,100,200,30);

    this->ImagePath_edit = new QLineEdit(this);
    this->ImagePath_edit->setReadOnly(true);
    this->ImagePath_edit->setGeometry(220,150,200,30);

    this->VideoPath_btn = new QPushButton("...",this);
    this->VideoPath_btn->setGeometry(430,100,30,30);

    this->ImagePath_btn = new QPushButton("...",this);
    this->ImagePath_btn->setGeometry(430,150,30,30);

    //录制时长下拉框控件初始化
    this->Interval_box = new QComboBox(this);
    this->Interval_box->setGeometry(220,200,200,30);
    this->Interval_box->addItem("1分钟");
    this->Interval_box->addItem("2分钟");
    this->Interval_box->addItem("3分钟");
    this->Interval_box->setFont(ft2);

    //摄像头下拉框控件初始化
    this->Camera_box = new QComboBox(this);
    this->Camera_box->setGeometry(220,250,200,30);
    this->Camera_box->setFont(ft2);
    //获取摄像头
    QList<QString> cnames= Decode::getcamera();
    this->Camera_box->addItems(cnames);

    this->OK_btn = new QPushButton("确定",this);
    this->OK_btn->setGeometry(220,300,60,30);
    OK_btn->setFont(ft2);

    this->Esc_btn = new QPushButton("取消",this);
    this->Esc_btn->setGeometry(340,300,60,30);
    Esc_btn->setFont(ft2);

}

//连接函数
void SetWidget::init_connect()
{
    connect(this->VideoPath_btn,SIGNAL(clicked()),this,SLOT(Select_VideoPath()));
    connect(this->ImagePath_btn,SIGNAL(clicked()),this,SLOT(Select_ImagePath()));
    connect(this->OK_btn,SIGNAL(clicked()),this,SLOT(init_data()));
    connect(this->OK_btn,SIGNAL(clicked()),this,SLOT(getmain()));
}

//设置信息存储函数
void SetWidget::init_data()
{
    //framecount时长换算，60分钟=1000毫秒
    int framecount = 0;
    if(Interval_box->currentIndex() == 0)
    {
        framecount =1500;
    }
    if(Interval_box->currentIndex() == 1)
    {
        framecount =3000;
    }
    if(Interval_box->currentIndex() == 2)
    {
        framecount =4500;
    }
    //如果路径不为空
    if(VideoPath_edit->text().trimmed() != tr("") && ImagePath_edit->text().trimmed() != tr(""))
    {
        //先判断数据库里面是否有设置信息 mark 0为没有数据，1为有数据
        this->mark=SetControl::getInstance()->getSetting();
        int res;
        //如果没有设置信息，就存入数据库设置信息
        if(mark==0)
        {

            res=SetControl::getInstance()->doSet(this->VideoPath_edit->text().trimmed(),this->ImagePath_edit->text().trimmed(),
                                                     framecount,Camera_box->currentText());
        }
        //如果有设置信息，就更新数据库设置信息
        else
        {
            res=SetControl::getInstance()->updateSetting(this->VideoPath_edit->text().trimmed(),this->ImagePath_edit->text().trimmed(),
                                                         framecount,Camera_box->currentText());
        }
        //存入数据库信息 0表示成功，1表示失败
        if(res==0)
        {
            QMessageBox:: information(this,"提示","设置成功","确定");
            emit tomain();
        }
        else
        {
            QMessageBox:: information(this,"提示","设置失败","确定");
        }
    }
    //路径为空就提示
    else
    {
        QMessageBox:: information(this,"提示","路径不能为空","确定");
    }
}

//跳转到主界面函数
void SetWidget::getmain()
{
    //如果mark 0为有数据，就不用设置就跳到主界面
    if(mark==0)
    {
        this->close();
        Main_Widget *mainwidget = new Main_Widget();
        mainwidget->show();
    }
    else
    {
        this->close();
    }

}

//视频路径选择窗口函数
void SetWidget::Select_VideoPath()
{
    QString Video_path=QFileDialog::getExistingDirectory(this,"选择视频存储路径","../");
    if(Video_path != nullptr)
    {
        //显示到编辑框上
        this->VideoPath_edit->setText(Video_path);
    }

}

//图片路径选择窗口函数
void SetWidget::Select_ImagePath()
{
    QString Image_path=QFileDialog::getExistingDirectory(this,"选择视频存储路径","../");
    if(Image_path != nullptr)
    {
        //显示到编辑框上
        this->ImagePath_edit->setText(Image_path);
    }

}



