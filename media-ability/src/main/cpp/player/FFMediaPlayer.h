//
// Created by 魏魏金鹏 on 2023/12/13.
//

#ifndef COMPILE_FFMEDIAPLAYER_H
#define COMPILE_FFMEDIAPLAYER_H

#include "MediaPlayer.h"

class FFMediaPlayer : public MediaPlayer{
public:
    FFMediaPlayer(){};
    virtual ~FFMediaPlayer(){};
    virtual void Init(JNIEnv *jniEnv, jobject obj, char *url, int renderType, jobject surface);
    virtual void UnInit();

    virtual void Play();
    virtual void Pause();
    virtual void Stop();
    virtual void SeekToPosition(float position);
    virtual long GetMediaParams(int paramType);

private:
    virtual JNIEnv *GetJNIEnv(bool *isAttach);
    virtual jobject GetJavaObj();
    virtual JavaVM *GetJavaVM();

    static void PostMessage(void *context, int msgType, float msgCode);

    VideoDecoder *m_VideoDecoder = nullptr;
    AudioDecoder *m_AudioDecoder = nullptr;

    VideoRender *m_VideoRender = nullptr;
    AudioRender *m_AudioRender = nullptr;
};

#endif //COMPILE_FFMEDIAPLAYER_H
