#include <jni.h>

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
        (JNIEnv *env, jclass cls)
{
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

JNIEXPORT jstring JNICALL
Java_com_ffmpeg_media_1ability_FFmpegKit_nativeVersion(JNIEnv *env, jclass clazz) {
    const char *version = av_version_info();
    return env->NewStringUTF(version);
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


}