//
// Created by 魏魏金鹏 on 2023/12/19.
//

#ifndef COMPILE_NUDEVIDEODECODER_H
#define COMPILE_NUDEVIDEODECODER_H

extern "C" {
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libavutil/frame.h>
#include <libswscale/swscale.h>
#include <libavcodec/jni.h>
};

#include <thread>
#include <jni.h>
#include <render/video/VideoRender.h>

#define MAX_PATH   2048
#define DELAY_THRESHOLD 100 //100ms

using namespace std;


class NudeVideoDecoder{
public:
    NudeVideoDecoder(){};

    virtual ~NudeVideoDecoder(){};

    int Nude_H264DecoderInit();

    int Nude_H264Decode(uint8_t *inbuf, int inbufSize);

private:

    int Nude_VideoDecoderInit(AVCodecParameters *ctx);

    int Nude_VideoDecoderRelease();

    virtual void OnDecoderReady();
    virtual void OnDecoderDone();
    virtual void OnFrameAvailable(AVFrame *frame);

    const AVPixelFormat DST_PIXEL_FORMAT = AV_PIX_FMT_RGBA;

    int m_VideoWidth = 0;
    int m_VideoHeight = 0;

    int m_RenderWidth = 0;
    int m_RenderHeight = 0;

    AVFrame *m_RGBAFrame = nullptr;
    uint8_t *m_FrameBuffer = nullptr;

    VideoRender *m_VideoRender = nullptr;
    SwsContext *m_SwsContext = nullptr;

    //封装格式上下文
    AVFormatContext *m_AVFormatContext = nullptr;
    //解码器上下文
    AVCodecContext  *m_AVCodecContext = nullptr;
    //解码器
    AVCodec         *m_AVCodec = nullptr;
    //编码的数据包
    AVPacket        *m_Packet = nullptr;
    //解码的帧
    AVFrame         *m_Frame = nullptr;

    SwsContext   *m_SmsContext ;


};


#endif //COMPILE_NUDEVIDEODECODER_H
