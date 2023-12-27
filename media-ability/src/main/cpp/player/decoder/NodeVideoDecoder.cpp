//
// Created by 魏魏金鹏 on 2023/12/19.
//

#include "NudeVideoDecoder.h"
#include "../../util/LogUtil.h"
#include "LogUtil.h"


int NudeVideoDecoder::Nude_H264DecoderInit() {

    LOGCATE("Nude_H264DecoderInit111");

    AVCodec *pAVCodec = avcodec_find_decoder(AV_CODEC_ID_HEVC);
    if (!pAVCodec) {
        LOGCATE("can not find H264 codec\n");
        return -1;
    }

    AVCodecContext *pAVCodecCtx = avcodec_alloc_context3(pAVCodec);
    if (pAVCodecCtx == NULL) {
        LOGCATE("Could not alloc video context!\n");
        return -2;
    }

    AVCodecParameters *codecParameters = avcodec_parameters_alloc();
    if (avcodec_parameters_from_context(codecParameters, pAVCodecCtx) < 0) {
        LOGCATE("Failed to copy avcodec parameters from codec context.");
        avcodec_parameters_free(&codecParameters);
        avcodec_free_context(&pAVCodecCtx);
        return -3;
    }

    int ret = Nude_VideoDecoderInit(codecParameters);
    avcodec_parameters_free(&codecParameters);
    avcodec_free_context(&pAVCodecCtx);

    return ret;
}

int NudeVideoDecoder::Nude_VideoDecoderInit(AVCodecParameters *codecParameters) {
    if (!codecParameters) {
        LOGCATE("Source codec context is NULL.");
        return -1;
    }

    m_AVCodec = avcodec_find_decoder(codecParameters->codec_id);

    if (!m_AVCodec) {
        LOGCATE("Can not find codec:%d\n", codecParameters->codec_id);
        return -2;
    }
    m_AVCodecContext = avcodec_alloc_context3(m_AVCodec);
    if (!m_AVCodecContext) {
        LOGCATE("Failed to alloc codec context.");
        Nude_VideoDecoderRelease();
        return -3;
    }

    if (avcodec_parameters_to_context(m_AVCodecContext, codecParameters) < 0) {
        LOGCATE("Failed to copy avcodec parameters to codec context.");
        Nude_VideoDecoderRelease();
        return -3;
    }

    if (avcodec_open2(m_AVCodecContext, m_AVCodec, NULL) < 0) {
        LOGCATE("Nude_H264Decoder:::Failed to open h264 decoder");
        Nude_VideoDecoderRelease();
        return -4;
    }

    m_Packet = av_packet_alloc();

    m_Frame = av_frame_alloc();
    return 0;
}

int NudeVideoDecoder::Nude_VideoDecoderRelease() {

    if (m_AVCodecContext != NULL) {
        avcodec_free_context(&m_AVCodecContext);
        m_AVCodecContext = NULL;
    }

    if (m_Frame != NULL) {
        av_packet_unref(m_Packet);
        av_free(m_Frame);
        m_Frame = NULL;
    }

    if (m_SmsContext) {
        sws_freeContext(m_SmsContext);
    }

    if (m_Packet != NULL) {
        av_packet_unref(m_Packet);
    }

    return 0;
}

int NudeVideoDecoder::Nude_H264Decode(uint8_t *inbuf, int inbufSize) {

    if (!m_AVCodecContext || !m_Frame || !inbuf || inbufSize <= 0) {
        LOGCATE("Nude_H264Decode:::return -1;=%d", -1);
        return -1;
    }

    m_Packet->data = inbuf;
    m_Packet->size = inbufSize;
    LOGCATE("Nude_H264Decode:::m_Packet=%d", m_Packet->size);
    int ret = avcodec_send_packet(m_AVCodecContext, m_Packet);

    if (ret == 0) {
        ret = avcodec_receive_frame(m_AVCodecContext, m_Frame);
        if (ret == 0) {
//            framePara[0] = m_Frame->width;
//            framePara[1] = m_Frame->height;
//
//            if (outYUVBuf) {
//                *outYUVBuf = (unsigned char *)m_Frame->data;
//                framePara[2] = m_Frame->linesize[0];
//                framePara[3] = m_Frame->linesize[1];
//                framePara[4] = m_Frame->linesize[2];
//            }
//            else if (outRGBBuf) {
//                m_FrameYUV->data[0] = outRGBBuf;
//                m_FrameYUV->data[1] = NULL;
//                m_FrameYUV->data[2] = NULL;
//                m_FrameYUV->data[3] = NULL;
//                int linesize[4] = { m_AVCodecContext->width * 3, m_AVCodecContext->height * 3, 0, 0 };
//                m_SmsContext = sws_getContext(m_AVCodecContext->width, m_AVCodecContext->height, AV_PIX_FMT_YUV420P, m_AVCodecContext->width, m_AVCodecContext->height, AV_PIX_FMT_RGB24, SWS_FAST_BILINEAR, NULL, NULL, NULL);
//                sws_scale(m_SmsContext, (const uint8_t* const *) m_Frame->data, m_Frame->linesize, 0, m_AVCodecContext->height, m_FrameYUV->data, linesize);
//                sws_freeContext(m_SmsContext);
//
//                return 1;
//            }
        } else if (ret == AVERROR(EAGAIN)) {
            return 0;
        } else {
            return -1;
        }
    }

    return 0;
}

