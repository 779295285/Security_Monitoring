#include "main_replaywidget.h"

Main_ReplayWidget::Main_ReplayWidget(QWidget *parent) : QWidget(parent)
{

    this->page=1;
    init_UI();
//    lastvideo_play();
//    init_connect();

}
//界面布局
void Main_ReplayWidget::init_UI()
{
    //视频回放布局初始化
    this->totalLayout = new QHBoxLayout();
    this->leftLayout = new QVBoxLayout();
    this->leftWidget = new QWidget();
    this->rightLayout = new QVBoxLayout();
    this->rightWidget = new QWidget();
    this->rightLayout2 = new QHBoxLayout();
    this->rightWidget2 = new QWidget();
    this->midLayout = new QVBoxLayout();
    this->midWidget = new QWidget();
    this->rightBottomWidget =new QWidget();
    this->rightBottomLayout = new QHBoxLayout();
    this->righttopWidget =new QWidget();
    this->righttopLayout= new QVBoxLayout();
    this->StackedWidget =new QStackedWidget();
    this->video_btn = new QPushButton("视频回放",this);
    this->image_btn = new QPushButton("图片列表",this);

    //视频回放---设置左边和右边背景颜色
    this->leftWidget->setStyleSheet("background:gray");
    this->righttopWidget->setStyleSheet("background:gray");

    //视频回放---右边视频回放、图片回放按钮布局
    this->leftLayout->addWidget(video_btn);
    this->leftLayout->addWidget(image_btn);
    //视频回放---设置弹簧，使两个按钮放到顶部
    this->leftLayout->addStretch(0);
    this->leftWidget->setLayout(leftLayout);

    //视频回放---中间布局
    this->video_label = new QLabel();
    this->video_label2 = new QLabel();
    this->midLayout->addWidget(video_label,7);
    this->midLayout->addWidget(video_label2,3);
    this->video_label->setMinimumSize(750,420);
    this->midWidget->setLayout(midLayout);

    //视频回放---右边视频列表布局
    this->playList = new QListWidget;
    //设置QListWidget中单元项的间距
    playList-> setSpacing(0) ;
    //设置自动适应布局调整(Adjust适应， Fixed不适应)，默认不适应
    playList-> setResizeMode (QListWidget::Adjust) ;
    //设置不能移动
    playList-> setMovement (QListWidget::Static) ;
    playList->setStyleSheet("border:none;font-size:15px");
    playList->setIconSize(QSize(120,130));

    QList<QString> titleList;
    QList<QString> coverList;
    //从数据库获取视频信息,返回qres
    char **qres;
    qres=VideoControl::getInstance()->getVideoPath();
    //用List存视频路径，跳过表头，自增2存一次
    for(int i=VideoModel::col;i<(VideoModel::row+1)*VideoModel::col;i+=2)
    {
        titleList<<qres[i];
    }
    //用List存封面路径，跳过表头，自增2存一次
    for(int i=VideoModel::col+1;i<(VideoModel::row+1)*VideoModel::col;i+=2)
    {
        coverList<<qres[i];
    }
    //将得到的list添加到QListWidgetItem单元项里面
    for (int i=0;i<titleList.size();i++)
    {
        //定义QListWidgetItem对象
        QListWidgetItem *playItem = new QListWidgetItem ;
        //为单元项设置属性
        //设置
        playItem->setIcon(QIcon(coverList[i]));
        playItem->setTextColor("white");
        playItem->setText(titleList.at(i));
        //重新设置单元项图片的宽度和高度
        playItem->setSizeHint(QSize(150,170));
        //将单元项添加到QListWidget中
        playList->addItem(playItem);
    }
    //将视频列表添加到布局里
    this->righttopLayout->addWidget(playList) ;
    this->righttopWidget->setLayout(righttopLayout);

    //视频回放---右边日历查询布局
    this->Inquire_btn = new QPushButton("查询",this);
    //日历控件初始化
    this->date = new QDateEdit();
    this->date->setCalendarPopup(true);
    this->date->setDate(QDate::currentDate());
    this->date->setFixedSize(160,40);
    //查询和日历控件添加到布局里
    this->rightBottomLayout->addWidget(date);
    this->rightBottomLayout->addWidget(Inquire_btn);
    this->rightBottomWidget->setLayout(rightBottomLayout);

    //日历查询布局和视频列表布局比例为1:9
    this->rightLayout->addWidget(rightBottomWidget,1);
    this->rightLayout->addWidget(righttopWidget,9);
    this->rightWidget->setLayout(rightLayout);

    //视频播放布局和视频列表布局比例为7：3
    this->rightLayout2->addWidget(midWidget,7);
    this->rightLayout2->addWidget(rightWidget,3);
    this->rightWidget2->setLayout(rightLayout2);

    //将视频回放布局添加到堆栈布局里
    this->StackedWidget->addWidget(rightWidget2);

    //图片回放布局初始化
    this->leftWidget1=new QWidget();
    this->bottomWidget=new QWidget();
    this->rightWidget3=new QWidget();
    this->rightWidget4=new QWidget();
    this->topWidget=new QWidget();
    this->leftLayout1=new QVBoxLayout();
    this->bottomLayout=new QHBoxLayout();
    this->rightLayout3=new QVBoxLayout();
    this->rightLayout4=new QHBoxLayout();
    this->topLayout=new QGridLayout();

    //图片回放控件初始化
    this->name_label=new QLabel("照片名称：",this);
    this->size_label=new QLabel("照片大小：",this);
    this->resolution_label=new QLabel("照片尺寸：",this);
    this->Next_btn = new QPushButton("下一页",this);
    this->Previous_btn = new QPushButton("上一页",this);

    //图片回放---中间图片列表布局
    this->image_List = new QListWidget;
    //设置QListWidget的显示模式
    image_List-> setViewMode (QListView::IconMode);
    //设置QListWidget中单元项的间距
    image_List-> setSpacing(4);
    //设置自动适应布局调整(Adjust适应， Fixed不适应)，默认不适应
    image_List-> setResizeMode (QListWidget::Adjust) ;
    //设置不能移动
    image_List-> setMovement (QListWidget::Static) ;
    image_List->setStyleSheet("border:none;font-size:15px");
    image_List->setIconSize(QSize(230,230));

    QList<QString> ImageList;
    QList<QString> nameList;
    //从数据库获取图片信息,返回qres
    char **qres2;
    qres2=ImageControl::getInstance()->getImagePath(page);
    //用List存视频路径，跳过表头，自增2存一次
    for(int i=ImageModel::col;i<(ImageModel::row+1)*ImageModel::col;i+=2)
    {
        ImageList<<qres2[i];
    }
    //用List存视频名称，跳过表头，自增2存一次
    for(int i=ImageModel::col+1;i<(ImageModel::row+1)*ImageModel::col;i+=2)
    {
        nameList<<qres2[i];
    }
    //将得到的list添加到QListWidgetItem单元项里面
    for (int i=0;i<ImageList.size();i++)
    {
        //定义QListWidgetItem对象
        QListWidgetItem *imageItem = new QListWidgetItem;
        //为单元项设置属性
        //设置
        imageItem->setIcon(QIcon(ImageList[i]));
        imageItem->setText(nameList.at(i));
        //重新设置单元项图片的宽度和高度
        imageItem->setSizeHint(QSize(220,220));
        //将单元项添加到QListWidget中
        image_List->addItem(imageItem);
    }
    //将图片列表添加到布局里
    this->topLayout->addWidget(image_List);
    this->topWidget->setLayout(topLayout);

    //图片回放---中间下边翻页布局
    this->bottomLayout->addWidget(Previous_btn);
    this->bottomLayout->addWidget(Next_btn);
    this->bottomWidget->setLayout(bottomLayout);

    //图片回放---中间图片列表布局和下边翻页布局比例为95:5
    this->leftLayout1->addWidget(topWidget,95);
    this->leftLayout1->addWidget(bottomWidget,5);
    this->leftWidget1->setLayout(leftLayout1);

    //图片回放---右边图片信息布局
    this->rightLayout3->addWidget(name_label);
    this->rightLayout3->addWidget(size_label);
    this->rightLayout3->addWidget(resolution_label);
    //图片回放---用弹簧把label设置到布局顶部
    this->rightLayout3->addStretch(0);
    this->rightWidget3->setLayout(rightLayout3);
    //图片列表布局和图片信息布局比例为8:2
    this->rightLayout4->addWidget(leftWidget1,8);
    this->rightLayout4->addWidget(rightWidget3,2);
    this->rightWidget4->setLayout(rightLayout4);

    this->StackedWidget->addWidget(rightWidget4);
    this->StackedWidget->setCurrentWidget(rightWidget2);
    //总布局
    this->totalLayout ->setSpacing(0);
    this->totalLayout->setMargin(0);
    this->totalLayout->addWidget(leftWidget,15);
    this->totalLayout->addWidget(StackedWidget,85);
    this->setLayout(totalLayout);
}
//连接函数
void Main_ReplayWidget::init_connect()
{
    //连接函数,将信号发送者对象中的信号signal与接受者对象中的slot连接
    connect(playList,SIGNAL(itemClicked(QListWidgetItem *)),this,SLOT(click_video(QListWidgetItem *)));
    connect(video_btn,SIGNAL(clicked()),this,SLOT(tovideo()));
    connect(image_btn,SIGNAL(clicked()),this,SLOT(toimage()));
    connect(Previous_btn,SIGNAL(clicked()),this,SLOT(previous()));
    connect(Next_btn,SIGNAL(clicked()),this,SLOT(next()));
    connect(Inquire_btn,SIGNAL(clicked()),this,SLOT(calendar_query()));
    connect(decodeThread, SIGNAL(sendImg2(QImage)), this, SLOT(receiveimg(QImage)));
    connect(image_List, SIGNAL(itemClicked(QListWidgetItem *)), this, SLOT(click_image(QListWidgetItem *)));

}
//更新视频列表函数
void Main_ReplayWidget::videolist()
{
    //更新视频列表
    //删去所有item
    this->playList->deleteLater();
    this->playList =new QListWidget();
    this->righttopLayout->deleteLater();
    this->righttopLayout= new QVBoxLayout();
    this->righttopWidget->deleteLater();
    this->righttopWidget=new QWidget();


    //设置QListWidget的显示模式
    //设置QListWidget中单元项的间距
    playList-> setSpacing(0) ;
    //设置自动适应布局调整(Adjust适应， Fixed不适应)，默认不适应
    playList-> setResizeMode (QListWidget::Adjust) ;
    //设置不能移动
    playList-> setMovement (QListWidget::Static) ;
    playList->setStyleSheet("border:none;font-size:15px");
    playList->setIconSize(QSize(120,130));

    char **qres;
    qres=VideoControl::getInstance()->getVideoPath();

    QList<QString> titleList;
    QList<QString> coverList;
    for(int i=VideoModel::col;i<(VideoModel::row+1)*VideoModel::col;i+=2)
    {
        titleList<<qres[i];
    }
    for(int i=VideoModel::col+1;i<(VideoModel::row+1)*VideoModel::col;i+=2)
    {
        coverList<<qres[i];
    }
    for (int i=0;i<titleList.size();i++)
    {
        //定义QListWidgetItem对象
        QListWidgetItem *playItem = new QListWidgetItem ;
        //为单元项设置属性
        //设置
        playItem->setIcon(QIcon(coverList[i]));
        playItem->setText(titleList.at(i));
        //重新设置单元项图片的宽度和高度
        playItem->setSizeHint(QSize(150,170));
        //将单元项添加到QListWidget中
        playList->addItem(playItem);
    }
    this->righttopLayout->addWidget(playList);
    this->righttopWidget->setLayout(righttopLayout);
    this->righttopWidget->setStyleSheet("background:gray");
    this->rightLayout->addWidget(righttopWidget,9);
    connect(playList,SIGNAL(itemClicked(QListWidgetItem *)),this,SLOT(click_video(QListWidgetItem *)));
}
//更新图片列表函数
void Main_ReplayWidget::imagelist()
{

    //更新视频列表
    //删去所有item
    this->image_List->deleteLater();
    this->image_List =new QListWidget();
    this->topLayout->deleteLater();
    this->topLayout= new QGridLayout();
    this->topWidget->deleteLater();
    this->topWidget=new QWidget();

    //设置QListWidget的显示模式
    image_List-> setViewMode (QListView::IconMode);
    //设置QListWidget中单元项的间距
    image_List-> setSpacing(4);
    //设置自动适应布局调整(Adjust适应， Fixed不适应)，默认不适应
    image_List-> setResizeMode (QListWidget::Adjust) ;
    //设置不能移动
    image_List-> setMovement (QListWidget::Static) ;
    image_List->setStyleSheet("border:none;font-size:15px");
    image_List->setIconSize(QSize(230,230));


    QList<QString> ImageList;
    QList<QString> nameList;
    char **qres2;
    qres2=ImageControl::getInstance()->getImagePath(this->page);
    for(int i=ImageModel::col;i<(ImageModel::row+1)*ImageModel::col;i+=2)
    {
        ImageList<<qres2[i];

    }
    for(int i=ImageModel::col+1;i<(ImageModel::row+1)*ImageModel::col;i+=2)
    {
        nameList<<qres2[i];
    }

    for (int i=0;i<ImageList.size();i++)
    {
        //定义QListWidgetItem对象
        QListWidgetItem *imageItem = new QListWidgetItem;
        //为单元项设置属性
        //设置
        imageItem->setIcon(QIcon(ImageList[i]));
        imageItem->setText(nameList.at(i));
        //重新设置单元项图片的宽度和高度
        imageItem->setSizeHint(QSize(220,220));
        //将单元项添加到QListWidget中
        image_List->addItem(imageItem);
    }
    //重新添加到布局里面
    this->topLayout->addWidget(image_List);
    this->topWidget->setLayout(topLayout);
    this->leftLayout1->addWidget(topWidget,95);
    this->leftLayout1->addWidget(bottomWidget,5);
    connect(image_List, SIGNAL(itemClicked(QListWidgetItem *)), this, SLOT(click_image(QListWidgetItem *)));

}
//回放最后一个视频函数
void Main_ReplayWidget::lastvideo_play()
{
    //从数据库获取最后一个视频路径
    char**res;
    res=VideoModel::getInstance()->getLastvideo();
    QString lastvdieo =res[1];
    //如果没有就返回
    if(lastvdieo.length()==0)
    {
        QMessageBox::warning(this, tr("提示！"),tr("暂无视频可播放！"),QMessageBox::Yes);
        return;
    }
    //找到就传路径给解码线程并且打开
    this->decodeThread=new Decode_Replay(lastvdieo);
    this->decodeThread->start();

}


//槽函数--点击视频列表播放视频
void Main_ReplayWidget::click_video(QListWidgetItem *item)
{
    //通过点击item获取对应的text，也就是视频名称，再传给control层去查询数据库
    char **qres=VideoControl::getInstance()->getVideo(item->text());
    replayWidget =new Play_Widget(qres[1]);
    replayWidget->show();
}

//点击图片槽函数
void Main_ReplayWidget::click_image(QListWidgetItem *item)
{
    //获取该item的text，即图片名字，然后到数据库查询图片路径
    int size;
    char **qres=ImageControl::getInstance()->getimage(item->text());
    QFile myfile(qres[1]);
    //获取图片大小
    if(myfile.open(QIODevice::ReadOnly))
    {
        size = myfile.size();
        myfile.close();
    }
    //获取图片宽高
    this->image_size.load(qres[1]);
    this->name_label->setText("图片名称："+item->text());
        this->size_label->setText("图片大小："+QString::number(size/1024)+" KB");
        this->resolution_label->setText("照片尺寸："+QString::number(image_size.height())
                                        +" X "+QString::number(image_size.width()));

    //获得图片路径，加载出图片放大窗口
    this->ImageWidget=new Image_Widegt(qres[1]);
    this->ImageWidget->show();
}
//切换视频列表函数
void Main_ReplayWidget::tovideo()
{
    //用堆栈布局显示视频列表布局
    this->StackedWidget->setCurrentWidget(rightWidget2);
}
//切换图片列表函数
void Main_ReplayWidget::toimage()
{
    //用堆栈布局显示图片列表布局
    this->StackedWidget->setCurrentWidget(rightWidget4);
    imagelist();
}
//图片列表下一页函数
void Main_ReplayWidget::next()
{   //先判断数据库下一个区间是否还有图片
    this->page++;
    char **qres3;
    QList<QString> ImageList;
    qres3=ImageControl::getInstance()->getImagePath(this->page);
    for(int i=ImageModel::col;i<(ImageModel::row+1)*ImageModel::col;i+=1)
    {
        ImageList<<qres3[i];
    }
     //如果没有就提示，并恢复原来页数
    if(ImageList.size()==0)
    {
       QMessageBox::warning(this, tr("提示！"),tr("已经是最后一页！"),QMessageBox::Yes);
       this->page--;
    }
    //否则加加载图片
    else
    {
        imagelist();
    }
}

//图片列表上一页函数
void Main_ReplayWidget::previous()
{
    //如果页数不是第一页就继续加载图片
    if(this->page>1)
    {
        this->page--;
        imagelist();
    }
    //如果页数是第一页就提示
    else
    {
        QMessageBox::warning(this, tr("提示！"),tr("已经是第一页！"),QMessageBox::Yes);
    }
}

//日历查询函数
void Main_ReplayWidget::calendar_query()
{
    //获取日历控件的参数，并修改格式yyyyMMdd
    QString time = date->dateTime().toString("yyyyMMdd");
    //control层传参查询数据库是否有该日期视频
    char **qres;
    qres=VideoControl::getInstance()->calendar_query(time);
    QList<QString> titleList;
    QList<QString> coverList;
    for(int i=VideoModel::col;i<(VideoModel::row+1)*VideoModel::col;i+=2)
    {
        titleList<<qres[i];
    }
    //如果没有就提示，并返回
    if(titleList.size()==0)
    {
       QMessageBox::warning(this, tr("提示！"),tr("没有该日期视频数据！"),QMessageBox::Yes);
       return;
    }
    //如果有就删除布局，并重新new出来
    this->playList->deleteLater();
    this->playList =new QListWidget();
    this->righttopLayout->deleteLater();
    this->righttopLayout= new QVBoxLayout();
    this->righttopWidget->deleteLater();
    this->righttopWidget=new QWidget();

    playList-> setSpacing(0) ;
    //设置自动适应布局调整(Adjust适应， Fixed不适应)，默认不适应
    playList-> setResizeMode (QListWidget::Adjust) ;
    //设置不能移动
    playList-> setMovement (QListWidget::Static) ;
    playList->setStyleSheet("border:none;font-size:15px");
    playList->setIconSize(QSize(110,120));


    for(int i=VideoModel::col+1;i<(VideoModel::row+1)*VideoModel::col;i+=2)
    {
        coverList<<qres[i];
    }
    for (int i=0;i<titleList.size();i++)
    {
        //定义QListWidgetItem对象
        QListWidgetItem *playItem = new QListWidgetItem;
        //为单元项设置属性
        //设置
        playItem->setIcon(QIcon(coverList[i]));
        playItem->setText(titleList.at(i));
        //重新设置单元项图片的宽度和高度
        playItem->setSizeHint(QSize(150,250));
        //将单元项添加到QListWidget中
        playList->addItem(playItem);
    }
    this->righttopLayout->addWidget(playList);
    this->righttopWidget->setLayout(righttopLayout);
    this->righttopWidget->setStyleSheet("background:gray");
    this->rightLayout->addWidget(righttopWidget,9);
    connect(playList,SIGNAL(itemClicked(QListWidgetItem *)),this,SLOT(click_video(QListWidgetItem *)));
}
//视频回放界面接收图片函数
void Main_ReplayWidget::receiveimg(QImage img)
{
    this->Image =img;
    this->update();
}

//视频回放界面label控件接收图片事件
void Main_ReplayWidget::paintEvent(QPaintEvent *)
{
    if(!this->Image.isNull())
    {
        QPixmap *image = new QPixmap(QPixmap::fromImage(this->Image));
        image->scaled(video_label->size(),Qt::KeepAspectRatio);
        //控件接收图片
        video_label->setPixmap(QPixmap::fromImage(this->Image));
        video_label->setScaledContents(true);
    }
}



