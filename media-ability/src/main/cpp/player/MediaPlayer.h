//
// Created by 魏魏金鹏 on 2023/12/13.
//

#ifndef COMPILE_MEDIAPLAYER_H
#define COMPILE_MEDIAPLAYER_H

#include <jni.h>

#include <decoder/VideoDecoder.h>
#include <decoder/AudioDecoder.h>
#include <render/audio/AudioRender.h>

#define JAVA_PLAYER_EVENT_CALLBACK_API_NAME "playerEventCallback"

#define MEDIA_PARAM_VIDEO_WIDTH         0x0001
#define MEDIA_PARAM_VIDEO_HEIGHT        0x0002
#define MEDIA_PARAM_VIDEO_DURATION      0x0003

#define MEDIA_PARAM_ASSET_MANAGER       0x0020

//友元函数：允许一个函数访问类的私有和保护成员，friend void printPrivateData()
class MediaPlayer {
public:
    MediaPlayer(){};

    //析构函数：生命周期结束时调用
    //virtual修饰父类中的函数、修饰继承性；注意 友元函数、构造函数、static函数不能用virtual修饰，普通成员函数和析构函数可以使用
    virtual ~MediaPlayer() {};

    virtual void Init(JNIEnv *jniEnv, jobject obj, char *url, int renderType, jobject surface) = 0;

    virtual void UnInit() = 0;

    virtual void Play() = 0;

    virtual void Pause() = 0;

    virtual void Stop() = 0;

    virtual void SeekToPosition(float position) = 0;

    virtual long GetMediaParams(int paramType) = 0;

    virtual void SetMediaParams(int paramType, jobject obj) {}

    virtual JNIEnv *GetJNIEnv(bool *isAttach) = 0;

    virtual jobject GetJavaObj() = 0;

    virtual JavaVM *GetJavaVM() = 0;

    JavaVM *m_JavaVM = nullptr;
    jobject m_JavaObj = nullptr;
};

#endif //COMPILE_MEDIAPLAYER_H
