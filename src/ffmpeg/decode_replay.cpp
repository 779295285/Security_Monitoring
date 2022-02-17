#include "decode_replay.h"
QString Decode_Replay::replay_path=nullptr;

Decode_Replay::Decode_Replay(QString path)
{
    this->videoIndex= -1; //记录视频流下标
    this->replay_path = path;
    this->play_speed=40;
    this->status=0;
    this->screenshots_mark=0;
}

Decode_Replay::~Decode_Replay()
{

}



void Decode_Replay::registerFFmpeg()
{
    av_register_all();
    avdevice_register_all();
}


int Decode_Replay::open_video()
{
    this->pformatContext=avformat_alloc_context();
    //封装格式上下文结构体，视频路径
    return avformat_open_input(&pformatContext,replay_path.toStdString().c_str(),nullptr,nullptr);
}

int Decode_Replay::find_stream()
{
    //获取视频文件信息、流数据、视频流
    int res= avformat_find_stream_info(pformatContext,nullptr);
    if(res!=0)
    {
        return res;
    }
    //查找是否存在视频流
    for(int i=0;i<this->pformatContext->nb_streams;i++)
    {
        if(pformatContext->streams[i]->codec->codec_type == AVMEDIA_TYPE_VIDEO)
        {
            this->videoIndex = i; //找到视频流下标
            break;
        }
    }
    return this->videoIndex;

}

int Decode_Replay::find_decoder()
{

    //找编解码器上下文结构体
    this->codec = pformatContext->streams[videoIndex]->codec;
    //找解码器
    this->decoder= avcodec_find_decoder(codec->codec_id);
    if(decoder == nullptr)
    {
        return -1;
    }
    //打开解码器
    return avcodec_open2(codec,decoder,nullptr);

}

void Decode_Replay::prepare_image()
{
    //一帧码流数据
    this->pkt=(AVPacket *)malloc(sizeof (AVPacket));   //开空间
    //准备像素数据

    picture = av_frame_alloc();
    rgbpicture = av_frame_alloc();  //rgbpicture去除有损数据的像素数据RGB32

    //----------------------RGB32像素数据准备---------------------------//
    //一帧图像数据大小
    int imgaeBytesRGB = avpicture_get_size(AV_PIX_FMT_RGB32,this->codec->width,this->codec->height);
    //动态开辟空间
    bufferRGB =(uint8_t *) av_malloc(imgaeBytesRGB *sizeof (uint8_t));
    //图片填充
    avpicture_fill((AVPicture *)rgbpicture,bufferRGB,AV_PIX_FMT_RGB32,this->codec->width,this->codec->height);
    //剔除规则
    swscontentRGB = nullptr;
    //制订剔除规则 编码格式
    swscontentRGB = sws_getContext(this->codec->width,this->codec->height,this->codec->pix_fmt,
                                this->codec->width,this->codec->height,AV_PIX_FMT_RGB32,
                                SWS_BICUBIC,nullptr,nullptr,nullptr);

}

void Decode_Replay::decode_frame()
{


    //一帧帧读取码流数据
    while(av_read_frame(pformatContext,pkt)==0)
    {
        while (status==1)
        {
            continue;
        }
        //读取码流数据 pkt
        if(videoIndex == pkt->stream_index)
        {
            int got_picture_ptr = -1;
            //解码picture：有损像素数据
            avcodec_decode_video2(codec,picture,&got_picture_ptr,pkt);
            if(got_picture_ptr!=0)
            {
                //剔除 得到纯净RGBpicture
                sws_scale(swscontentRGB,picture->data,picture->linesize,0,
                          picture->height,rgbpicture->data,rgbpicture->linesize);
                img = QImage((uchar *)bufferRGB,codec->width,codec->height,QImage::Format_RGB32);
                //发送信号到播放界面
                msleep(this->play_speed);
                emit sendImg2(img);
                if(this->screenshots_mark==1)
                {
                    QString image_name=this->getTime();
                    QString path=SetControl::getInstance()->getSetting_imagepath()+"/"+"shots_"+image_name+".jpg";
                    img.save(path);
                    ImageControl::getInstance()->addImagePath(image_name, path);
                    this->screenshots_mark=0;
                }

            }
        }
        //重置pkt
        av_packet_unref(pkt);
    }
}

void Decode_Replay::run()
{
    //整个解码操作
    //打开摄像头
    registerFFmpeg();
    if(open_video()!= 0)
    {
        return;
    }

    //流媒体数据
    if(find_stream()!= 0)
    {
        return;
    }
    //解码器
    if(find_decoder()!= 0)
    {
        return;
    }
    //读取码流数据
    prepare_image();
    decode_frame();
}

void Decode_Replay::setSpeed(QString speed)
{
    if(speed.compare("0.5X")==0)
    {
        this->play_speed=80;
    }
    else if(speed.compare("1X")==0)
    {
        this->play_speed=40;
    }
    else if(speed.compare("1.5X")==0)
    {
        this->play_speed=20;
    }
    else
    {
        this->play_speed=10;
    }
}


QString Decode_Replay::getTime()
{
    QDateTime currentdatetime = QDateTime::currentDateTime();
    QString currentdate = currentdatetime.toString("yyyyMMddHHmmss");
    return currentdate;
}




