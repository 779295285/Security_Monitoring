#include "loginwidget.h"
#include "main_widget.h"
//构造函数
loginWidget::loginWidget(QWidget *parent)
    : QWidget(parent)
{
    this->mark=0;
    init_UI();
    init_control();
    init_connect();
    this->code = this->getcode();
}

//登录窗口设置函数
void loginWidget::init_UI()
{
    this->setWindowTitle("LoginWin");
    this->setFixedSize(500,400);
    this->regWin = new RegisterWidget();
}

//登录窗口控件函数
void loginWidget::init_control()
{   //登录界面绘制
    this->user_label = new QLabel("用户名:",this);
    this->user_label->setGeometry(130,60,80,30);

    this->password_label = new QLabel("密码:",this);
    this->password_label->setGeometry(145,110,80,30);

    this->code_label = new QLabel("验证码:",this);
    this->code_label->setGeometry(130,160,80,30);

    this->user_edit = new QLineEdit(this);
    this->user_edit->setGeometry(190,60,150,30);
    this->user_edit->setPlaceholderText(tr("请输入用户名!"));
    this->user_edit->setMaxLength(12);
    this->user_edit->installEventFilter(this);

    this->password_edit = new QLineEdit(this);
    this->password_edit->setGeometry(190,110,150,30);
    this->password_edit->setPlaceholderText(tr("请输入密码!"));
    this->password_edit->setMaxLength(8);
    this->password_edit->setEchoMode(QLineEdit::Password);

    this->eye_btn = new QPushButton("..",this);
    this->eye_btn->setGeometry(350,110,30,30);

    this->Vericode_edit = new QLineEdit(this);
    this->Vericode_edit->setGeometry(190,160,80,30);
    this->Vericode_edit->setPlaceholderText(tr("验证码"));

    this->login_btn = new QPushButton("登录",this);
    this->login_btn->setGeometry(100,240,80,30);

    this->register_btn = new QPushButton("注册",this);
    this->register_btn->setGeometry(200,240,80,30);

    this->qsc_btn = new QPushButton("退出",this);
    this->qsc_btn->setGeometry(300,240,80,30);
}
//连接函数
void loginWidget::init_connect()
{
    connect(this->register_btn,SIGNAL(clicked()),this,SLOT(toreg()));
    connect(this->login_btn,SIGNAL(clicked()),this,SLOT(login()));
    connect(this->regWin,SIGNAL(back()),this,SLOT(backlog()));
    connect(this->eye_btn,SIGNAL(clicked()),this,SLOT(PlainAndCipher()));
}


//生成验证码函数
QString loginWidget::getcode()
{
    update();
    //code为QString类型变量
    QString getcode;
        //随机数字
        for(int i = 0;i < 4;++i)
        {
            int num = qrand()%3;
            if(num == 0)
            {
                //数字
                getcode += QString::number(qrand()%10);
            }
            else if(num == 1)
            {
                //大写字母
                int temp = 'A';
                getcode += static_cast<QChar>(temp + qrand()%26);
            } else if(num == 2)
            {
                //小写字母
                int temp = 'a';
                getcode += static_cast<QChar>(temp + qrand()%26);
            }
        }
        return getcode;

}

//登录验证函数
void loginWidget::login()
{

    //获得user_edit输入框的文本：user_edit->text()；
    //trimmed()去掉前后空格
    //tr()函数，防止设置中文时乱码
    int res=UserControl::getInstance()->doLogin(this->user_edit->text().trimmed(),GetMd5(this->password_edit->text().trimmed()));
    QString captcha = this->Vericode_edit->text();
    if(res==0)
    {

        if(captcha.toLower() == this->code.toLower())
        {
            QMessageBox::warning(this, tr("提示！"),tr("登录成功！"),QMessageBox::Yes);
            Main_Widget::status=1;
            user_edit->clear();
            password_edit->clear();
            Vericode_edit->clear();
            this->code = this->getcode();
            this->close();
            return;

        }

        else
        {
            QMessageBox::warning(this, tr("警告！"),tr("验证码错误！"),QMessageBox::Yes);


        }
    }
    else
    {                               //标题              内容                OK按钮
        QMessageBox::warning(this, tr("警告！"),tr("用户名或密码错误！"),QMessageBox::Yes);
    }
    // 清空输入框内容
    user_edit->clear();
    password_edit->clear();
    Vericode_edit->clear();
    this->code = this->getcode();
}

//验证码干扰元素函数
void loginWidget::paintEvent(QPaintEvent *event)
{

    QPainter painter(this);
    QPen pen;
    painter.drawPixmap(this->rect(),QPixmap(":image/pt.jpg"));

    //画点
    for(int i = 0;i < 100;++i)
    {
        pen = QPen(QColor(qrand()%256,qrand()%256,qrand()%256));
        painter.setPen(pen);
        painter.drawPoint(300+qrand()%150,160+qrand()%50);
    }

    //画线
    for(int i = 0;i < 10;++i)
    {

        painter.drawLine(300+qrand()%150,160+qrand()%50,
                         300+qrand()%150,160+qrand()%50);
    }
    pen = QPen(QColor(255,0,0,100));
    QFont font("楷体",25,QFont::Bold,true);
    painter.setFont(font);
    painter.setPen(pen);
    //绘画字
    for(int i = 0;i < 4;++i)
    {
        painter.drawText(300+30*i,160,30,40,Qt::AlignCenter,QString(code[i]));
    }


}

//重写鼠标点击事件，没点击一次就随机生成新的验证码
void loginWidget::mousePressEvent(QMouseEvent *event)
{
    //验证码区域做重写鼠标点击事件
    int x = event->x();
    int y = event->y();
    if(x>300 && x<450 && y>150 && y<200)
    {

        this->code = this->getcode();
    }
}

//明文密文显示函数
void loginWidget::PlainAndCipher()
{
    //0是密文 1是明文
    if(this->mark==0)
    {
        this->password_edit->setEchoMode(QLineEdit::Normal);
        this->mark=1;
    }
    else if(this->mark==1)
    {
        this->password_edit->setEchoMode(QLineEdit::Password);
        this->mark=0;
    }

}

//跳转到注册
void loginWidget::toreg()
{
    this->hide();
    this->regWin->show();

}
//返回到登录
void loginWidget::backlog()
{
    this->regWin->close();
    this->show();
}

QString loginWidget::GetMd5(const QString &value)
{
    QString md5;
    QByteArray bb;
    bb = QCryptographicHash::hash(value.toUtf8(), QCryptographicHash::Md5);
    md5.append(bb.toHex());
    return md5;
}

loginWidget::~loginWidget()
{

}
