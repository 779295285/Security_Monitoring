#include "encodetoh264.h"
int EncodeToH264::frame_count=0;
int EncodeToH264::width=0;
int EncodeToH264::height=0;
QQueue<AVFrame* > EncodeToH264::Queue_AVFrame;
QString EncodeToH264::name=nullptr;

EncodeToH264::EncodeToH264()
{
    this->pkt_index = 0;
    this->interval = 0;
    this->registerEncode();

}
//注册编码初始化
void EncodeToH264::registerEncode()
{
    av_register_all();
}

void EncodeToH264::guess_format(int width,int height)
{
    pkt = av_packet_alloc();
    pformatContext = avformat_alloc_context();
    this->video_path=SetControl::getInstance()->getSetting_videopath();
    this->path =video_path+"/"+name+".h264";
    this->interval=SetControl::getInstance()->getSetting_interval();

    this->outformat = av_guess_format(nullptr,path.toStdString().c_str(),nullptr);
    if(outformat == nullptr )
    {
        return;
    }
    //设置输出格式
    pformatContext->oformat = outformat;
    //打开视频流 输入输出上下文对象 输出文件路径 以写入方式操作
    int res=avio_open(&pformatContext->pb,path.toStdString().c_str(),AVIO_FLAG_WRITE);
    if(res!=0)
    {
        return;
    }
    //创建视频流
    this->newStream = avformat_new_stream(pformatContext,nullptr);
    if(newStream == nullptr)
    {
        return;
    }
    //编解码器上下文结构体
    codecContext = newStream->codec;

    //设置基本信息 1266 968
    codecContext->width=width;
    codecContext->height=height;
    codecContext->time_base={1,25};  //时间基，1s播放帧数
    codecContext->bit_rate =400000;  //码率
    codecContext->framerate={25,1};  //帧率
    codecContext->gop_size=10;       //10帧为一组

    //影响清晰度
    codecContext->qmax = 51;
    codecContext->qmin = 10;
    codecContext->max_b_frames = 0;                 //没有B帧
    codecContext->pix_fmt = AV_PIX_FMT_YUV420P;     //编码器格式
    codecContext->codec_type = AVMEDIA_TYPE_VIDEO;  //设置为视频流
    codecContext->codec_id = outformat->video_codec;//编码器id
    //编码器
    this->encoder = avcodec_find_encoder(codecContext->codec_id );
    res = avcodec_open2(codecContext,encoder,nullptr);
    if(res != 0)
    {
        return;
    }

    //写入头部信息 编码器打开成功即可写入编码头部信息，完成编码钱所有初始化工作
    res = avformat_write_header(pformatContext,nullptr);
    if(res != 0)
    {
        return;
    }
}

void EncodeToH264::encode_frame(AVFrame *yuvpicture)
{
    //yuv420p--->AVpacket--->写入h264文件
    //发送一帧像素数据-->编码器 frame ;YUV像素数据
    int res = avcodec_send_frame(codecContext,yuvpicture);
    if(res != 0)
    {
        return;
    }
    //编码的一帧像素数据给编码器进行编码的时候，可能一个AVPacket放不下，
    //就需要两个AVPacket,循环处理去接收码流数据
    while(res >= 0)
    {
        //接收一帧编码数据AVCodecContext *avctx，AVPacket *avpkt
        /*显示时间基，保证显示的顺序，定义一个变量，每次加+1,
        每次开始编码的时候赋值为0*/
        yuvpicture->pts = pkt_index++; //时间基 显示顺序
        res = avcodec_receive_packet(codecContext,pkt);
        if(res == AVERROR(EAGAIN)|| res == AVERROR_EOF)
        {
            break;
        }
        //写入文件就可以写入一帧数据
        av_interleaved_write_frame(pformatContext,pkt);
    }
    //这里的pkt使用完之后一定要记得重置
    av_packet_unref(pkt);
}

void EncodeToH264::writeTailer()
{
    av_write_trailer(pformatContext);
    //关闭输入流
    avio_close(pformatContext->pb);
    //释放视频信息
    avformat_free_context(pformatContext);
}

void EncodeToH264::run()
{
    this->guess_format(this->width,this->height);
    while(1)
    {
        if(!Queue_AVFrame.isEmpty())
        {
            //从队列取一帧进行编码，并从队列删除
            this->encode_frame(this->Queue_AVFrame.dequeue());
            frame_count++;
            cout<<frame_count<<endl;
            if(frame_count == interval)
            {
                //写入尾帧
                this->writeTailer();
                this->guess_format(this->width,this->height);
                //写入数据库--将视频路径写入到数据库当中
                VideoControl::getInstance()->addVideoPath(name+".h264",video_path+"/"+name+".jpg",video_path+"/"+name+".h264");
                //初始化
                frame_count = 0;
            }
        }
    }
    //写尾帧
    this->writeTailer();
}

void EncodeToH264::getHeightWidth(int width, int height)
{
    this->width=width;
    this->height=height;
}

void EncodeToH264::getName(QString name)
{
    this->name=name;
}


//获取日期时间--视频图片命名
QString EncodeToH264::getTime()
{
    QDateTime currentdatetime = QDateTime::currentDateTime();
    QString currentdate = currentdatetime.toString("yyyyMMddHHmmss");
    return currentdate;
}
