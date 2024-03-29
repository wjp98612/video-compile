package com.ffmpeg.media_ability;

import android.view.Surface;

public class FFmpegPlayer {

    public static final int VIDEO_GL_RENDER = 0;
    public static final int AUDIO_GL_RENDER = 1;
    public static final int VR_3D_GL_RENDER = 2;

    public static final int FFMEDIA_PLAYER = 0;

    public static final int HWCODEC_PLAYER = 1;



    static {
        System.loadLibrary("ffmpeg-invoke");
    }

    public static final int MSG_DECODER_INIT_ERROR      = 0;
    public static final int MSG_DECODER_READY           = 1;
    public static final int MSG_DECODER_DONE            = 2;
    public static final int MSG_REQUEST_RENDER          = 3;
    public static final int MSG_DECODING_TIME           = 4;

    public static final int MEDIA_PARAM_VIDEO_WIDTH     = 0x0001;
    public static final int MEDIA_PARAM_VIDEO_HEIGHT    = 0x0002;
    public static final int MEDIA_PARAM_VIDEO_DURATION  = 0x0003;

    public static final int MEDIA_PARAM_ASSET_MANAGER   = 0x0020;

    public static final int VIDEO_RENDER_OPENGL         = 0;
    public static final int VIDEO_RENDER_ANWINDOW       = 1;
    public static final int VIDEO_RENDER_3D_VR          = 2;

    private long mNativePlayerHandle = 0;

    private EventCallback mEventCallback = null;

    public void init(String url, int videoRenderType, Surface surface){
        mNativePlayerHandle = native_Init(url,FFMEDIA_PLAYER,videoRenderType,surface);
    }

    public void init(String url, int playerType, int videoRenderType, Surface surface) {
        mNativePlayerHandle = native_Init(url, playerType, videoRenderType, surface);
    }

    public void initNudeDecoder(int codecType,int width,int height){
        native_NudeDecoderInit(codecType,width,height,mNativePlayerHandle);
    }

    public void nudeDecode(byte[] data,int bufferSize){
        native_NudeDecode(data,bufferSize,true,mNativePlayerHandle);
    }

    public void addEventCallback(EventCallback callback) {
        mEventCallback = callback;
    }

    public void play(){
        native_Play(mNativePlayerHandle);
    }

    public void playBuffer(byte[] bytes){
        native_PlayWebRtc(bytes,false,mNativePlayerHandle);
    }

    public void pause(){
        native_Pause(mNativePlayerHandle);
    }

    public void stop(){
        native_Stop(mNativePlayerHandle);
    }

    public void seekToPosition(float position) {
        native_SeekToPosition(mNativePlayerHandle, position);
    }

    public void unInit() {
        native_UnInit(mNativePlayerHandle);
    }

    public long getMediaParams(int paramType) {
        return native_GetMediaParams(mNativePlayerHandle, paramType);
    }

    public void setMediaParams(int paramType, Object param) {
        native_SetMediaParams(mNativePlayerHandle, paramType, param);
    }

    private native long native_Init(String url, int playerType, int renderType, Object surface);

    private native void native_Play(long playerHandle);

    private native void native_PlayWebRtc(byte[] data,boolean isCoby,long playerHandle);

    private native void native_SeekToPosition(long playerHandle, float position);

    private native long native_GetMediaParams(long playerHandle, int paramType);

    private native void native_SetMediaParams(long playerHandle, int paramType, Object param);

    private native void native_NudeDecoderInit(int codecType,int width,int height,long playerHandle);

    private native void native_NudeDecode(byte[] data,int bufferSize,boolean isCoby,long playerHandle);

    public static native void native_OnSurfaceCreated(int renderType);
    public static native void native_OnSurfaceChanged(int renderType, int width, int height);
    public static native void native_OnDrawFrame(int renderType);

    public static native void native_SetGesture(int renderType, float xRotateAngle, float yRotateAngle, float scale);
    public static native void native_SetTouchLoc(int renderType, float touchX, float touchY);


    private native void native_Pause(long playerHandle);

    private native void native_UnInit(long playerHandle);

    private native void native_Stop(long playerHandle);

    private void playerEventCallback(int msgType, float msgValue) {
        if(mEventCallback != null)
            mEventCallback.onPlayerEvent(msgType, msgValue);
    }

    public interface EventCallback {
        void onPlayerEvent(int msgType, float msgValue);
    }
}
