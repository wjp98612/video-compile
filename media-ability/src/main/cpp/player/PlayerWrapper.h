//
// Created by 魏魏金鹏 on 2023/12/13.
//

#ifndef LEARNFFMPEG_PLAYERWRAPPER_H
#define LEARNFFMPEG_PLAYERWRAPPER_H

#include <jni.h>
#include <FFMediaPlayer.h>

static const int FFMEDIA_PLAYER = 0;
static const int HWCODEC_PLAYER = 1;

class PlayerWrapper {
public:
    PlayerWrapper(){};
    virtual ~PlayerWrapper(){};

    void Init(JNIEnv *jniEnv, jobject obj, char *url, int playerType, int renderType, jobject surface);
    void UnInit();

    void Play();
    void PlayWebRtc(uint8_t *buffer);
    void Pause();
    void Stop();
    void SeekToPosition(float position);
    long GetMediaParams(int paramType);
    void SetMediaParams(int paramType, jobject obj);
    void SetWebRtcParams(jobject obj);

private:
    MediaPlayer* m_MediaPlayer = nullptr;

};


#endif //LEARNFFMPEG_PLAYERWRAPPER_H
