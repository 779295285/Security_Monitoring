#include "decode.h"
Decode::Decode()
{
    this->videoIndex= -1; //记录视频流下标
    this->count = 0;
}
//获取摄像头
QList<QString> Decode::getcamera()
{

    QList<QString> cnames;
    cnames.clear();
    QList<QCameraInfo> cameras = QCameraInfo::availableCameras();
    //获取摄像头到list
    for(int i=0;i<cameras.size();i++)
    {
        cnames.push_back(cameras.at(i).description());
    }
    return cnames;
}


void Decode::registerFFmpeg()
{
    av_register_all();
    avdevice_register_all();
}

int Decode::open_camera()
{
    //开空间
    this->pformatContext=avformat_alloc_context();
    //封装格式上下文结构体，视频路径
    //return avformat_open_input(&pformatContext,"../video/haha.mp4",nullptr,nullptr);
    //获取摄像头
    QList<QString> cnames=getcamera();
    AVInputFormat *fmt = av_find_input_format("dshow");
    char CameraName[256];
    sprintf(CameraName, "video=%s", cnames[0].toStdString().c_str());
    return avformat_open_input(&pformatContext,CameraName,fmt,nullptr);
}


int Decode::find_stream()
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

int Decode::find_decoder()
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

void Decode::prepare_image()
{
    //一帧码流数据
    this->pkt=(AVPacket *)malloc(sizeof (AVPacket));   //开空间
    //准备像素数据

    picture = av_frame_alloc();
    yuvpicture = av_frame_alloc();  //yuvpicture去除有损数据的像素数据YUV420
    rgbpicture = av_frame_alloc();  //rgbpicture去除有损数据的像素数据RGB32
    yuvpicture->width = codec->width;
    yuvpicture->height = codec->height;
    yuvpicture->format = codec->pix_fmt;

    //初始化编码需要的所有数据
    //EncodeToH264::getHeightWidth(codec->width,codec->height);

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

     //----------------------YUV420P像素数据准备---------------------------//
     //一帧图像数据大小
     int imgaeBytesYUV = avpicture_get_size(AV_PIX_FMT_YUV420P,codec->width,codec->height);
     //动态开辟空间
     bufferYUV =(uint8_t *) av_malloc(imgaeBytesYUV *sizeof (uint8_t));
     //图片填充
     avpicture_fill((AVPicture *)yuvpicture,bufferYUV,AV_PIX_FMT_YUV420P,codec->width,codec->height);
     //剔除规则
     swscontentYUV = nullptr;
     //制订剔除规则 编码格式
     swscontentYUV = sws_getContext(codec->width,codec->height,codec->pix_fmt,
                                 codec->width,codec->height,AV_PIX_FMT_YUV420P,
                                 SWS_BICUBIC,nullptr,nullptr,nullptr);
}

void Decode::decode_frame()
{
     int mark=0;
     this->image_name=encodeObj->getTime();
     this->encodeObj = new EncodeToH264();
     this->encodeObj->getHeightWidth(codec->width,codec->height);   
     this->encodeObj->getName(image_name);
     this->encodeObj->start();


    //一帧帧读取码流数据
    while(av_read_frame(pformatContext,pkt)==0)
    {
        //读取码流数据 pkt
        if(videoIndex == pkt->stream_index)
        {
            int got_picture_ptr = -1;
            //解码picture：有损像素数据
            avcodec_decode_video2(codec,picture,&got_picture_ptr,pkt);
            if(got_picture_ptr!=0)
            {
                //剔除 得到纯净YUVpicture
                sws_scale(swscontentYUV,picture->data,picture->linesize,0,
                          picture->height,yuvpicture->data,yuvpicture->linesize);
                //剔除 得到纯净RGBpicture
                sws_scale(swscontentRGB,picture->data,picture->linesize,0,
                          picture->height,rgbpicture->data,rgbpicture->linesize);
                img = QImage((uchar *)bufferRGB,codec->width,codec->height,QImage::Format_RGB32);

                //发送信号到播放界面
                emit sendImg(img);
                //把YUV420P添加到队列中
                EncodeToH264::Queue_AVFrame.enqueue(yuvpicture);
                this->interval=SetControl::getInstance()->getSetting_interval();
                if(count==interval)
                {
                  //这里存放的是video第一帧的图片
                  //写入数据库--传到另一边一起写入
                    if(mark==1)
                    {
                        this->image_name=encodeObj->getTime();
                        encodeObj->getName(image_name);
                    }
                    mark=1;
                    QString path=SetControl::getInstance()->getSetting_imagepath()+"/"+image_name+".jpg";
                    this->count=0;
                    img.save(path);
                }
                this->count++;
            }
        }
        //重置pkt
        av_packet_unref(pkt);
    }
}

void Decode::run()
{
    //整个解码操作
    //打开摄像头
    registerFFmpeg();
    if(open_camera()!= 0)
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
    //解码
    decode_frame();

}





