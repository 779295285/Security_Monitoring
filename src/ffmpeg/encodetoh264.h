#ifndef ENCODETOH264_H
#define ENCODETOH264_H
#include <QDebug>
#include <QThread>
#include <QList>
#include <QQueue>
#include <QDateTime>
#include "controller/setcontrol.h"
#include "controller/videocontrol.h"
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

class EncodeToH264:public QThread
{

public:
    EncodeToH264();
    //注册组件
    void registerEncode();
    void guess_format(int width,int height);
    void encode_frame(AVFrame *yuvpicture);
    void writeTailer();

    void getHeightWidth(int width,int height);
    void getName(QString name);
    static int frame_count;
    //队列
    static QQueue<AVFrame *> Queue_AVFrame;
    QString getTime();
    QString path;
    QString video_path;
    static QString name;
    static int width;
    static int height;


    AVCodec *encoder;
    AVOutputFormat *outformat;
    AVStream *newStream;
private:
    AVCodecContext *codecContext;
    AVFormatContext *pformatContext;
    AVPacket *pkt;
    int pkt_index;
    int interval;
    void run();
};

#endif // ENCODETOH264_H
