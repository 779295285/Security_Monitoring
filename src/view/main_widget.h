#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QListWidget>
#include <QListWidgetItem>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QIcon>
#include <QPaintEvent>
#include<QDebug>
#include<QList>
#include<QComboBox>
#include<QImage>
#include<QPixmap>
#include<QStackedWidget>
#include<QTimer>
#include <QDateTime>
#include "main_monitorwidget.h"
#include "main_replaywidget.h"
#include "loginwidget.h"
#include "setwidget.h"
class Main_Widget : public QWidget
{
    Q_OBJECT
public:
    explicit Main_Widget(QWidget *parent = nullptr);

    void init_UI();
    void init_control();
    void init_connect();
    static int status;

private:
    QWidget *topWidget;
    QStackedWidget *bottomWidget;
    QLabel *time_label,*logo_label;
    QVBoxLayout *totalLayout;
    QHBoxLayout *topLayout;
    QPushButton *play_btn,*replay_btn,*log_btn,*setting_btn;
    QTimer *timer;
    Main_MonitorWidget *monitor;
    Main_ReplayWidget *replay;
    SetWidget *setting;
    loginWidget *loginwidget;
signals:

public slots:
    void qtimeSlot();
    void Tosetting();
    void Toreplay();
    void Tomonitor();
    void Tomain();
};

#endif // MAINWIDGET_H
