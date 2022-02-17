#ifndef DECODE_REPLAY_H
#define DECODE_REPLAY_H
#include <QDebug>
#include <QImage>
#include <QThread>
#include <QString>
#include <QQueue>
#include <QDateTime>
#include "controller/setcontrol.h"
#include "controller/imagecontrol.h"
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
class Decode_Replay:public QThread
{
    Q_OBJECT
public:
    Decode_Replay(QString path);
    ~Decode_Replay();

    //注册组件
    void registerFFmpeg();
    //打开视频
    int open_video();
    //流媒体数据
    int find_stream();
              //编解码器上下文结构体
    //找解码器
    int find_decoder();
    //准备图片帧
    void prepare_image();
    //读取码流数据
    void decode_frame();

    static QString replay_path;

    int status;
    int screenshots_mark;

private:
    AVFormatContext *pformatContext; //封装格式上下文结构体
    AVCodecContext *codec;
    AVCodec *decoder;

    AVPacket *pkt;
    AVFrame *picture,*rgbpicture; //picture有损像素数据 yuvpicture去除有损数据的像素数据
    SwsContext *swscontentRGB;
    uint8_t *bufferRGB;
    QImage img;
    int play_speed;
    int videoIndex;
    QString getTime();

protected:
    void run();
signals:
    void sendImg2(QImage img);
public slots:
    void setSpeed(QString speed);
};

#endif // DECODE_REPLAY_H
