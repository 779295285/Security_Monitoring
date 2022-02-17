#ifndef FTRANCETOMP4_H
#define FTRANCETOMP4_H
#include <QDebug>
#include <QString>
#include <QDateTime>
#include <QMessageBox>
#include <QAbstractButton>
#include <QThread>
#include "controller/setcontrol.h"
extern "C"
{
    #include "libavcodec/avcodec.h"       //编解码
    #include "libavdevice/avdevice.h"     //转码
    #include "libavfilter/avfilter.h"
    #include "libavformat/avformat.h"     //格式
    #include "libavutil/avutil.h"         //工具
    #include "libswresample/swresample.h"
    #include "libswscale/swscale.h"       //转置
}

class FTranceTomp4 : public QThread
{

public:
    FTranceTomp4();
    void openH264File(QString file);
    void coverTomp4();
    QString getTime();

private:
    AVFormatContext *pFormatContext,*outFormatContext;//输出的封装格式上下文结构体
    AVPacket *pkt;
    AVOutputFormat *outformat;
    int videoIndex,frameCount;
    AVStream *newStream;

};

#endif // FTRANCETODEST_H
