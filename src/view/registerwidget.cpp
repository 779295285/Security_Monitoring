#include "registerwidget.h"
//注册界面构造函数
RegisterWidget::RegisterWidget(QWidget *parent) : QWidget(parent)
{
    this->mark = 0;
    init_UI();
    init_control();
    init_connect();
}

//注册界面窗口设置函数
void RegisterWidget::init_UI()
{
    this->setWindowTitle("RegisterWindow");
    this->setFixedSize(500,400);
    this->setWindowIcon(QIcon(":image/login.png"));
}

//注册界面控件布局
void RegisterWidget::init_control()
{
    //validator为限制输入字符类型，只允许输入大小写、数字和下划线
    QRegExp account_regx("[a-zA-Z0-9_]+$");
    QValidator *validator = new QRegExpValidator(account_regx, this);

    this->account_label = new QLabel("账号:",this);
    this->account_label->setGeometry(150,40,80,30);

    this->user_label = new QLabel("用户名:",this);
    this->user_label->setGeometry(134,90,80,30);

    this->password_label = new QLabel("密码:",this);
    this->password_label->setGeometry(146,140,80,30);

    this->password_label2 = new QLabel("确认密码:",this);
    this->password_label2->setGeometry(120,190,80,30);

    this->account_edit = new QLineEdit(this);
    this->account_edit->setGeometry(190,40,150,30);
    this->account_edit->setPlaceholderText(tr("账号长度为8-12位"));
    this->account_edit->setValidator(validator);
    this->account_edit->setMaxLength(12);

    this->user_edit = new QLineEdit(this);
    this->user_edit->setGeometry(190,90,150,30);
    this->user_edit->setPlaceholderText(tr("用户名长度为8-12位"));
    this->user_edit->setValidator(validator);
    this->user_edit->setMaxLength(12);



    this->password_edit = new QLineEdit(this);
    this->password_edit->setGeometry(190,140,150,30);
    this->password_edit->setPlaceholderText(tr("密码长度为8-12位"));
    this->password_edit->setMaxLength(12);
    this->password_edit->setEchoMode(QLineEdit::Password);
    this->password_edit->setValidator(validator);

    this->password_edit2 = new QLineEdit(this);
    this->password_edit2->setGeometry(190,190,150,30);
    this->password_edit2->setPlaceholderText(tr("请输入密码!"));
    this->password_edit2->setMaxLength(12);
    this->password_edit2->setEchoMode(QLineEdit::Password);
    this->password_edit2->setValidator(validator);

    this->eye_btn =new QPushButton("...",this);
    this->eye_btn->setGeometry(350,190,30,30);

    this->register_btn = new QPushButton("注册",this);
    this->register_btn->setGeometry(100,250,80,30);

    this->qsc_btn = new QPushButton("取消",this);
    this->qsc_btn->setGeometry(300,250,80,30);

}

//连接函数
void RegisterWidget::init_connect()
{
    connect(this->qsc_btn,SIGNAL(clicked()),this,SIGNAL(back()));
    connect(this->register_btn,SIGNAL(clicked()),this,SLOT(regist()));
    connect(this->eye_btn,SIGNAL(clicked()),this,SLOT(PlainAndCipher()));
}

//注册函数
void RegisterWidget::regist()
{
    //如果编辑框为空，就提示
    if(this->user_edit->text().trimmed() == tr("") || this->password_edit->text() == tr("")
            ||this->password_edit2->text() == tr("") )
    {
            QMessageBox::warning(this, tr("提示！"),tr("内容不能为空！"),QMessageBox::Yes);
            // 清空输入框内容
            user_edit->clear();
            password_edit->clear();
            password_edit2->clear();
            //光标定位
            user_edit->setFocus();
    }
    else
    {
        //如果长度大于8就继续判断
        if(this->account_edit->text().length()>7 && this->user_edit->text().length()>7 &&
           this->password_edit->text().length()>7 && this->password_edit2->text().length()>7)
        {
            //如果密码和二次输入的密码一致就继续判断
            if(this->password_edit->text() == this->password_edit2->text())
            {
                //数据库查询是否存在该账号
                int res=UserControl::getInstance()->doReister(this->account_edit->text().trimmed(),this->user_edit->text().trimmed(),
                                                              GetMd5(this->password_edit->text().trimmed()));
                //res为0就注册成功
                if(res==0)
                {
                    QMessageBox::warning(this, tr("提示！"),tr("注册成功！"),QMessageBox::Yes);
                    // 清空输入框内容
                    user_edit->clear();
                    password_edit->clear();
                    password_edit2->clear();
                    //注册成功后就发送信号跳到登录
                    back();
                }
                //res为1就注册失败，该用户存在
                else if(res==1)
                {
                    QMessageBox::warning(this, tr("提示！"),tr("该用户已经存在！"),QMessageBox::Yes);
                    // 清空输入框内容
                    account_edit->clear();
                    user_edit->clear();
                    password_edit->clear();
                    password_edit2->clear();
                }
            }
            else
            {
                QMessageBox::warning(this, tr("提示！"),tr("密码不一致！"),QMessageBox::Yes);
                // 清空输入框内容
                account_edit->clear();
                user_edit->clear();
                password_edit->clear();
                password_edit2->clear();
                //光标定位
                user_edit->setFocus();
            }
        }
        else
        {
            if(this->account_edit->text().length()<8)
            {
                QMessageBox::warning(this, tr("提示！"),tr("账号长度为8-12位！"),QMessageBox::Yes);
            }
            else if (this->user_edit->text().length()<8)
            {
                QMessageBox::warning(this, tr("提示！"),tr("用户名长度为8-12位！"),QMessageBox::Yes);
            }
            else if (this->password_edit->text().length()<8)
            {
                QMessageBox::warning(this, tr("提示！"),tr("密码长度为8-12位！"),QMessageBox::Yes);
            }
            else if (this->password_edit2->text().length()<8)
            {
                QMessageBox::warning(this, tr("提示！"),tr("密码长度为8-12位！"),QMessageBox::Yes);
            }
            // 清空输入框内容
            account_edit->clear();
            user_edit->clear();
            password_edit->clear();
            password_edit2->clear();
            //光标定位
            user_edit->setFocus();
        }


    }
}
//明文密文切换函数
void RegisterWidget::PlainAndCipher()
{
    //0是密文 1是明文
    if(this->mark==0)
    {
        this->password_edit->setEchoMode(QLineEdit::Normal);
        this->password_edit2->setEchoMode(QLineEdit::Normal);
        this->mark=1;
    }
    else if(this->mark==1)
    {
        this->password_edit->setEchoMode(QLineEdit::Password);
        this->password_edit2->setEchoMode(QLineEdit::Password);
        this->mark=0;
    }

}
//回车键来确定注册
void RegisterWidget::keyPressEvent(QKeyEvent *event)
{
    if(event->key() ==Qt::Key_Return)
    {
        regist();
    }
}


QString RegisterWidget::GetMd5(const QString &value)
{
    QString md5;
    QByteArray bb;
    bb = QCryptographicHash::hash(value.toUtf8(), QCryptographicHash::Md5);
    md5.append(bb.toHex());
    return md5;
}
