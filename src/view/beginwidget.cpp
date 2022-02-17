#include "beginwidget.h"
//构造函数
BeginWidget::BeginWidget()
{
    this->setting=new SetWidget();
    init_UI();
    init_control();
    init_connect();
}

void BeginWidget::init_UI()
{
    //设置窗口标题
    this->setWindowTitle("安防监控系统");
    //设置窗口大小
    this->setFixedSize(780,500);
    //设置背景图
    this->setBackgroundBrush(QBrush(QPixmap(":png/background.jpeg")));

}

void BeginWidget::init_control()
{
    //创建场景
    this->scene = new QGraphicsScene();
    this->setScene(scene);
    //设置场景坐标和视图一致
    this->setSceneRect(0,0,this->width()-2,this->height()-2);

    //创建图元
    item1 = new MyItem(":png/1.png",1);
    item2 = new MyItem(":png/2.png",2);

    //设置图元开始位置
    item1->setPos(125,this->height()/2);
    item2->setPos(638,this->height()/2);

    //场景添加图元
    scene->addItem(item1);
    scene->addItem(item2);

    //定时器
    timer = new QTimer();
    timer->start(25);

}

void BeginWidget::init_connect()
{
    //场景的槽函数: advance 作用:触发每一-个图元的advance(int)-->图元移动
    connect(timer, SIGNAL(timeout()), scene, SLOT(advance()));
    //场景的槽函数: watchStatus 作用:观察图元状态--状态改变就停止
    connect(timer, SIGNAL(timeout()), this, SLOT(watchStatus()));
    //场景的槽函数: tologin 作用:跳转窗口
    connect(this->item2,SIGNAL(end()),this,SLOT(toSettingorMainWidget()));

}
//图元状态监控函数
void BeginWidget::watchStatus()
{
    //判断状态图元状态，变成1就停止
    if(this->item1->status == 1)
    {
        this->timer->stop();
    }
}
//设置界面跳转
void BeginWidget::toSettingorMainWidget()
{
    //开机动画隐藏
    this->hide();
    //从数据库查询是否有设置参数
    int mark = SetControl::getInstance()->getSetting();
    //如果没有就跳到设置页面
    if(mark != 0)
    {
         this->Main=new Main_Widget();
         this->Main->show();
    }
    //否则跳转主界面
    else
    {
        this->setting->show();
    }
}
