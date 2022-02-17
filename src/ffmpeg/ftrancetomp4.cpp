#include "ftrancetomp4.h"

FTranceTomp4::FTranceTomp4()
{
    this->videoIndex =-1;
    this->frameCount = 0;
    pFormatContext = avformat_alloc_context();
    outFormatContext =avformat_alloc_context();
    pkt = av_packet_alloc();
}

void FTranceTomp4::openH264File(QString file)
{
    av_register_all();
    QString path=SetControl::getInstance()->getSetting_videopath()+"/"+getTime()+".mp4";
    //打开视频文件
    int res= avformat_open_input(&pFormatContext,file.toStdString().c_str(),nullptr,nullptr);
    if(res!=0)
    {
        return;
    }
    //查找视频流
    avformat_find_stream_info(pFormatContext,nullptr);
    if(res!=0)
    {
        return;
    }
    for(int i=0;i<pFormatContext->nb_streams;i++)
    {
        if(pFormatContext->streams[i]->codec->codec_type == AVMEDIA_TYPE_VIDEO)
        {
            videoIndex = i;
            break;
        }
    }
    if(videoIndex == -1)
    {
        return;
    }
    outformat = av_guess_format(nullptr,path.toStdString().c_str(),nullptr);
    if(outformat == nullptr )
    {
        return;
    }
    //设置输出格式
    outFormatContext->oformat = outformat;
    //打开视频流 输入输出上下文对象 输出文件路径 以写入方式操作

    res=avio_open(&outFormatContext->pb,path.toStdString().c_str(),AVIO_FLAG_WRITE);
    if(res!=0)
    {
        return;
    }
    //创建视频流
    this->newStream = avformat_new_stream(outFormatContext,nullptr);
    if(newStream == nullptr)
    {
        return;
    }

    //参数设置把输入h264编码器的参数给输出视频流进行使用
    //参数1: 目标视频流的编码器参数信息结构体
    //参数2:输入视频流的编码器参数信息结构体
    avcodec_parameters_copy(newStream->codecpar,pFormatContext->streams[videoIndex]->codecpar);
    //写入头部信息 编码器打开成功即可写入编码头部信息，完成编码钱所有初始化工作
    res = avformat_write_header(outFormatContext,nullptr);
    if(res != 0)
    {
        return;
    }
}

void FTranceTomp4::coverTomp4()
{
    while(av_read_frame(pFormatContext,pkt)==0)
    {
        //判断是不是视频流
        if(pkt->stream_index == videoIndex)
        {
            //转码  重新编码  时间基设置  时间践
            //I帧首帧保存一 帧大部分 的重要的视频信息: P按照I帧: B按照左右两边的解码
            //一组一组解码
            frameCount++;
            //判断有没有设置显示时间基：没有设置的情况下
            if(pkt->pts == AV_NOPTS_VALUE)
            {
                //时间基的转换
                AVRational time_base1 = pFormatContext->streams[videoIndex]->time_base;
                //计算两帧之前的长度:转换
                int64_t duration = (double)AV_TIME_BASE/
                        av_q2d(pFormatContext->streams[videoIndex]->r_frame_rate);
                //计算显示时间基：（当前帧数*两帧之间的长度）/（输入时间基 *AV_TIME_BASE）
                pkt->pts=(double)(frameCount*duration)/
                         (double)(av_q2d(time_base1)*AV_TIME_BASE);
                //解码时间基=显示时间基
                pkt->dts = pkt->pts;
                pkt->duration = duration/(double)(av_q2d(time_base1)*AV_TIME_BASE);

            }
            else if (pkt->pts<pkt->dts)
            {
                //时间基小于解码时间基
                continue;
            }
            pkt->pts=av_rescale_q_rnd(pkt->pts, pFormatContext->streams[videoIndex]->time_base,
                                      newStream->time_base,
                                      (AVRounding)(AV_ROUND_INF|AV_ROUND_PASS_MINMAX));
            //解码时间基的转换
            pkt->dts=av_rescale_q_rnd(pkt->dts, pFormatContext->streams[videoIndex]->time_base,
                                      newStream->time_base,
                                      (AVRounding)(AV_ROUND_INF|AV_ROUND_PASS_MINMAX));
            //数据的时长，以所属媒体流的时间基准为单位，末知则值为默认值0
            pkt->duration=av_rescale_q(pkt->duration, pFormatContext->streams[videoIndex]->time_base,
                                       newStream->time_base);
            pkt->pos = -1;
            pkt->flags |= AV_PKT_FLAG_KEY;
            pkt->stream_index = 0;
            //写入数据到输出视频信息结构体汇总
            av_interleaved_write_frame(outFormatContext,pkt);
        }
        //重置pkt
        av_packet_unref(pkt);
    }

    //写入尾帧
    av_write_trailer(outFormatContext);

    //关闭编码器
    avcodec_close(outFormatContext->streams[videoIndex]->codec);
    av_free(&outFormatContext->streams[videoIndex]->codec);
    //关闭输出流
    avio_close(outFormatContext->pb);
    //释放outFormatContext
    av_free(outFormatContext);
    //关闭输入流
    avformat_close_input(&pFormatContext);
    //释放输入视频信息结构体
    av_free(pFormatContext);
    //释放包
    av_packet_free(&pkt);
}


//获取日期时间--视频图片命名
QString FTranceTomp4::getTime()
{
    QDateTime currentdatetime = QDateTime::currentDateTime();
    QString currentdate = currentdatetime.toString("yyyyMMddHHmmss");
    return currentdate;
}

