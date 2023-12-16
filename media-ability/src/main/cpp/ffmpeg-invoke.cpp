#include <jni.h>
#include "PlayerWrapper.h"

#include <render/video/VideoGLRender.h>
#include <render/video/VRGLRender.h>
#include <render/audio/OpenSLRender.h>

extern "C" {
#include <libavutil/avutil.h>
#include "libavcodec/avcodec.h"
#include "android/log.h"
#include "libavformat/avformat.h"
#include "libavutil/error.h"
#include <libavutil/imgutils.h>
#include <libswscale/swscale.h>
#include "android/bitmap.h"
#include "ffmpeg//ffmpeg.h"


#define logDebug(...) __android_log_print(ANDROID_LOG_DEBUG,"MainActivity",__VA_ARGS__)

JNIEXPORT jstring JNICALL Java_com_ffmpeg_media_1ability_FFmpegKit_native_1GetFFmpegVersion
        (JNIEnv *env, jclass cls) {
    char strBuffer[1024 * 4] = {0};
    strcat(strBuffer, "libavcodec : ");
    strcat(strBuffer, AV_STRINGIFY(LIBAVCODEC_VERSION));
    strcat(strBuffer, "\nlibavformat : ");
    strcat(strBuffer, AV_STRINGIFY(LIBAVFORMAT_VERSION));
    strcat(strBuffer, "\nlibavutil : ");
    strcat(strBuffer, AV_STRINGIFY(LIBAVUTIL_VERSION));
    strcat(strBuffer, "\nlibavfilter : ");
    strcat(strBuffer, AV_STRINGIFY(LIBAVFILTER_VERSION));
    strcat(strBuffer, "\nlibswresample : ");
    strcat(strBuffer, AV_STRINGIFY(LIBSWRESAMPLE_VERSION));
    strcat(strBuffer, "\nlibswscale : ");
    strcat(strBuffer, AV_STRINGIFY(LIBSWSCALE_VERSION));
    strcat(strBuffer, "\navcodec_configure : \n");
    strcat(strBuffer, avcodec_configuration());
    strcat(strBuffer, "\navcodec_license : ");
    strcat(strBuffer, avcodec_license());


    //ASanTestCase::MainTest();

    return env->NewStringUTF(strBuffer);
}


JNIEXPORT jint JNICALL
Java_com_ffmpeg_media_1ability_FFmpegKit_main(JNIEnv *env, jclass clazz, jobjectArray cmd) {
    int argc = env->GetArrayLength(cmd);
    logDebug("argc == %d", argc);
    char *argv[argc];

    for (int i = 0; i < argc; ++i) {
        jstring str = (jstring) env->GetObjectArrayElement(cmd, i);
        argv[i] = (char *) env->GetStringUTFChars(str, JNI_FALSE);
        logDebug("%s ", argv[i]);
    }

    return main(argc, argv);
}

/*
 * Class:     com_byteflow_learnffmpeg_media_FFMediaPlayer
 * Method:    native_Init
 * Signature: (JLjava/lang/String;Ljava/lang/Object;)J
 */
JNIEXPORT jlong JNICALL Java_com_ffmpeg_media_1ability_FFmpegPlayer_native_1Init
        (JNIEnv *env, jobject obj, jstring jurl, int playerType, jint renderType, jobject surface) {
    const char *url = env->GetStringUTFChars(jurl, nullptr);
    PlayerWrapper *player = new PlayerWrapper();
    player->Init(env, obj, const_cast<char *>(url), playerType, renderType, surface);
    env->ReleaseStringUTFChars(jurl, url);
    return reinterpret_cast<jlong>(player);
}

/*
 * Class:     com_byteflow_learnffmpeg_media_FFMediaPlayer
 * Method:    native_Play
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_com_ffmpeg_media_1ability_FFmpegPlayer_native_1Play(JNIEnv *env, jobject obj, jlong player_handle) {
    if (player_handle != 0) {
        PlayerWrapper *pPlayerWrapper = reinterpret_cast<PlayerWrapper *>(player_handle);
        pPlayerWrapper->Play();
    }

}

JNIEXPORT void JNICALL
Java_com_ffmpeg_media_1ability_FFmpegPlayer_native_1PlayWebRtc(JNIEnv *env, jobject obj,jbyteArray data,jlong player_handle) {

    if (data == NULL){
        logDebug("jbyteArray->frame buffer is null");
        return;
    }
    jsize length = env->GetArrayLength(data);

    uint8_t *buffer = new uint8_t[length];

    jbyte* bytes = env->GetByteArrayElements(data, nullptr);
    std::memcpy(buffer, bytes, length);
    env->ReleaseByteArrayElements(data, bytes, JNI_ABORT);

    if (player_handle != 0) {
        PlayerWrapper *pPlayerWrapper = reinterpret_cast<PlayerWrapper *>(player_handle);
        pPlayerWrapper->PlayWebRtc(buffer);
    }

}

JNIEXPORT void JNICALL
Java_com_ffmpeg_media_1ability_FFmpegPlayer_native_1SeekToPosition(JNIEnv *env, jobject thiz,
                                                                   jlong player_handle,
                                                                   jfloat position) {
    if (player_handle != 0) {
        PlayerWrapper *ffMediaPlayer = reinterpret_cast<PlayerWrapper *>(player_handle);
        ffMediaPlayer->SeekToPosition(position);
    }
}

JNIEXPORT jlong JNICALL
Java_com_ffmpeg_media_1ability_FFmpegPlayer_native_1GetMediaParams(JNIEnv *env, jobject thiz,
                                                                   jlong player_handle,
                                                                   jint param_type) {
    long value = 0;
    if (player_handle != 0) {
        PlayerWrapper *ffMediaPlayer = reinterpret_cast<PlayerWrapper *>(player_handle);
        value = ffMediaPlayer->GetMediaParams(param_type);
    }
    return value;
}

extern "C"
JNIEXPORT void JNICALL
Java_com_ffmpeg_media_1ability_FFmpegPlayer_native_1SetWebRtcParams(JNIEnv *env, jobject thiz,
                                                                    jlong player_handle,
                                                                   jobject param) {
    if (player_handle != 0) {
        PlayerWrapper *pPlayerWrapper = reinterpret_cast<PlayerWrapper *>(player_handle);
        pPlayerWrapper->SetWebRtcParams(param);
    }
}

extern "C"
JNIEXPORT void JNICALL
Java_com_ffmpeg_media_1ability_FFmpegPlayer_native_1SetMediaParams(JNIEnv *env, jobject thiz,
                                                                   jlong player_handle,
                                                                   jint param_type,
                                                                   jobject param) {
    if (player_handle != 0) {
        PlayerWrapper *ffMediaPlayer = reinterpret_cast<PlayerWrapper *>(player_handle);
        ffMediaPlayer->SetMediaParams(param_type, param);
    }
}

/*
 * Class:     com_byteflow_learnffmpeg_media_FFMediaPlayer
 * Method:    native_Pause
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_com_ffmpeg_media_1ability_FFmpegPlayer_native_1Pause
        (JNIEnv *env, jobject obj, jlong player_handle) {
    if (player_handle != 0) {
        PlayerWrapper *ffMediaPlayer = reinterpret_cast<PlayerWrapper *>(player_handle);
        ffMediaPlayer->Pause();
    }
}

/*
 * Class:     com_byteflow_learnffmpeg_media_FFMediaPlayer
 * Method:    native_Stop
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_com_ffmpeg_media_1ability_FFmpegPlayer_native_1Stop
        (JNIEnv *env, jobject obj, jlong player_handle) {
    if (player_handle != 0) {
        PlayerWrapper *ffMediaPlayer = reinterpret_cast<PlayerWrapper *>(player_handle);
        ffMediaPlayer->Stop();
    }
}



/*
 * Class:     com_byteflow_learnffmpeg_media_FFMediaPlayer
 * Method:    native_UnInit
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_com_ffmpeg_media_1ability_FFmpegPlayer_native_1UnInit
        (JNIEnv *env, jobject obj, jlong player_handle) {
    if (player_handle != 0) {
        PlayerWrapper *ffMediaPlayer = reinterpret_cast<PlayerWrapper *>(player_handle);
        ffMediaPlayer->UnInit();
        delete ffMediaPlayer;
    }
}

JNIEXPORT void JNICALL
Java_com_ffmpeg_media_1ability_FFmpegPlayer_native_1OnSurfaceCreated(JNIEnv *env,
                                                                     jclass clazz,
                                                                     jint render_type) {
    switch (render_type) {
        case VIDEO_GL_RENDER:
            VideoGLRender::GetInstance()->OnSurfaceCreated();
            break;
        case AUDIO_GL_RENDER:
            AudioGLRender::GetInstance()->OnSurfaceCreated();
            break;
        case VR_3D_GL_RENDER:
            VRGLRender::GetInstance()->OnSurfaceCreated();
            break;
        default:
            break;
    }
}

JNIEXPORT void JNICALL
Java_com_ffmpeg_media_1ability_FFmpegPlayer_native_1OnSurfaceChanged(JNIEnv *env, jclass clazz,
                                                                     jint render_type,
                                                                     jint width,
                                                                     jint height) {
    switch (render_type) {
        case VIDEO_GL_RENDER:
            VideoGLRender::GetInstance()->OnSurfaceChanged(width, height);
            break;
        case AUDIO_GL_RENDER:
            AudioGLRender::GetInstance()->OnSurfaceChanged(width, height);
            break;
        case VR_3D_GL_RENDER:
            VRGLRender::GetInstance()->OnSurfaceChanged(width, height);
            break;
        default:
            break;
    }
}

JNIEXPORT void JNICALL
Java_com_ffmpeg_media_1ability_FFmpegPlayer_native_1OnDrawFrame(JNIEnv *env, jclass clazz,
                                                                jint render_type) {
    switch (render_type) {
        case VIDEO_GL_RENDER:
            VideoGLRender::GetInstance()->OnDrawFrame();
            break;
        case AUDIO_GL_RENDER:
            AudioGLRender::GetInstance()->OnDrawFrame();
            break;
        case VR_3D_GL_RENDER:
            VRGLRender::GetInstance()->OnDrawFrame();
            break;
        default:
            break;
    }
}

JNIEXPORT void JNICALL
Java_com_ffmpeg_media_1ability_FFmpegPlayer_native_1SetGesture(JNIEnv *env, jclass clazz,
                                                               jint render_type,
                                                               jfloat x_rotate_angle,
                                                               jfloat y_rotate_angle,
                                                               jfloat scale) {
    switch (render_type) {
        case VIDEO_GL_RENDER:
            VideoGLRender::GetInstance()->UpdateMVPMatrix(x_rotate_angle, y_rotate_angle, scale,
                                                          scale);
            break;
        case AUDIO_GL_RENDER:
            AudioGLRender::GetInstance()->UpdateMVPMatrix(x_rotate_angle, y_rotate_angle, scale,
                                                          scale);
            break;
        case VR_3D_GL_RENDER:
            VRGLRender::GetInstance()->UpdateMVPMatrix(x_rotate_angle, y_rotate_angle, scale,
                                                       scale);
            break;
        default:
            break;
    }
}

JNIEXPORT void JNICALL
Java_com_ffmpeg_media_1ability_FFmpegPlayer_native_1SetTouchLoc(JNIEnv *env, jclass clazz,
                                                                jint render_type,
                                                                jfloat touch_x,
                                                                jfloat touch_y) {
    switch (render_type) {
        case VIDEO_GL_RENDER:
            VideoGLRender::GetInstance()->SetTouchLoc(touch_x, touch_y);
            break;
        case AUDIO_GL_RENDER:
            AudioGLRender::GetInstance()->SetTouchLoc(touch_x, touch_y);
            break;
        case VR_3D_GL_RENDER:
            VRGLRender::GetInstance()->SetTouchLoc(touch_x, touch_y);
            break;
        default:
            break;
    }
}


}