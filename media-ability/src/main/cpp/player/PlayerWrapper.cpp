//
// Created by 魏魏金鹏 on 2023/12/13.
//

#include "PlayerWrapper.h"
#include "HWCodecPlayer.h"

void PlayerWrapper::Init(JNIEnv *jniEnv, jobject obj, char *url, int playerType, int renderType,
                         jobject surface) {
    switch (playerType) {
        case FFMEDIA_PLAYER:
            m_MediaPlayer = new FFMediaPlayer();
            break;
        case HWCODEC_PLAYER:
            m_MediaPlayer = new HWCodecPlayer();
            break;
        default:
            break;
    }

    if(m_MediaPlayer)
        m_MediaPlayer->Init(jniEnv, obj, url, renderType, surface);
}

void PlayerWrapper::UnInit() {
    if(m_MediaPlayer) {
        m_MediaPlayer->UnInit();
        delete m_MediaPlayer;
        m_MediaPlayer = nullptr;
    }
}

void PlayerWrapper::Play() {
    if(m_MediaPlayer) {
        m_MediaPlayer->Play();
    }
}

void PlayerWrapper::PlayWebRtc(uint8_t *buffer) {
    if(m_MediaPlayer) {
        m_MediaPlayer->PlayWebRtc(buffer);
    }
}

void PlayerWrapper::Nude_H264DecoderInit(int codecType, int width, int height) {

    if(m_MediaPlayer) {
        m_MediaPlayer->Nude_H264DecoderInit(codecType,width,height);
    }
}

void PlayerWrapper::Nude_H264Decode(unsigned char * inbuf, int inbufSize) {

    if(m_MediaPlayer) {
        m_MediaPlayer->Nude_H264Decode(inbuf,inbufSize);
    }
}

void PlayerWrapper::Pause() {
    if(m_MediaPlayer) {
        m_MediaPlayer->Pause();
    }
}

void PlayerWrapper::Stop() {
    if(m_MediaPlayer) {
        m_MediaPlayer->Stop();
    }
}

void PlayerWrapper::SeekToPosition(float position) {
    if(m_MediaPlayer) {
        m_MediaPlayer->SeekToPosition(position);
    }

}

long PlayerWrapper::GetMediaParams(int paramType) {
    if(m_MediaPlayer) {
        return m_MediaPlayer->GetMediaParams(paramType);
    }

    return 0;
}

void PlayerWrapper::SetMediaParams(int paramType, jobject obj) {
    if(m_MediaPlayer) {
        m_MediaPlayer->SetMediaParams(paramType, obj);
    }
}

