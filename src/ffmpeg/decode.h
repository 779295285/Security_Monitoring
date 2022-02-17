#ifndef DECODE_H
#define DECODE_H
#include <QDebug>
#include <QImage>
#include <QThread>
#include <QString>
#include <QCameraInfo>
#include <QQueue>
#include "encodetoh264.h"

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

class Decode:public QThread
{
    Q_OBJECT
public:
    Decode();
    //注册组件
    void registerFFmpeg();
    //打开视频
    int open_camera();

    int open_video();
    //流媒体数据
    int find_stream();
              //编解码器上下文结构体
    //找解码器
    int find_decoder();
    void prepare_image();
    //读取码流数据
    void decode_frame();

    static QList<QString> getcamera();

private:
    AVFormatContext *pformatContext; //封装格式上下文结构体
    AVCodecContext *codec;
    AVCodec *decoder;

    AVPacket *pkt;
    AVFrame *yuvpicture, *picture,*rgbpicture; //picture有损像素数据 yuvpicture去除有损数据的像素数据
    SwsContext *swscontentRGB,*swscontentYUV;
    uint8_t *bufferRGB,*bufferYUV;
    QImage img;
    int videoIndex;
    int count;
    int interval;
    EncodeToH264 *encodeObj;
    QString image_name;
protected:
    void run();
signals:
    void sendImg(QImage img);
};

#endif // DECODETOH264_H
