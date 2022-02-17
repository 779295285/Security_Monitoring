#ifndef SETWIDGET_H
#define SETWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>

#include <QLineEdit>
#include <QButtonGroup>
#include <QComboBox>
#include <QCheckBox>
#include <QIcon>
#include <QMessageBox>
#include <QKeyEvent>
#include<QDebug>
#include <QCameraInfo>
#include <QFileDialog>
#include "ffmpeg/decode.h"
#include "controller/setcontrol.h"

class SetWidget:public QWidget
{
    Q_OBJECT
public:
    SetWidget();
    void init_UI();
    void init_control();
    void init_connect();
    int mark;

private:
   QLabel *Set_label,*VideoPath_label,*ImagePath_label,
          *Interval_label,*Camera_label;
   QPushButton *VideoPath_btn,*ImagePath_btn,
               *OK_btn,*Esc_btn;
   QLineEdit *VideoPath_edit,*ImagePath_edit;
   QComboBox *Interval_box,*Camera_box;


public slots:
   void Select_VideoPath();
   void Select_ImagePath();
   void init_data();
   void getmain();

signals:
   void tomain();


};

#endif // SETWIDGET_H
