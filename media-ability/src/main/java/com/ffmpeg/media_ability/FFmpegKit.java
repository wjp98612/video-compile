package com.ffmpeg.media_ability;

import android.os.AsyncTask;

public class FFmpegKit {

    public interface KitInterface {
        void onStart();

        void onProgress(int progress);

        void onEnd(int result);
    }

    static {
        System.loadLibrary("ffmpeg-invoke");
    }

    public static int execute(String[] commands) {
        return main(commands);
    }
    //
    public static String getInfo() {
        return native_GetFFmpegVersion();
    }

    public static void execute(String[] commands, final KitInterface kitIntenrface) {
        new AsyncTask<String[], Integer, Integer>() {
            @Override
            protected void onPreExecute() {
                if (kitIntenrface != null) {
                    kitIntenrface.onStart();
                }
            }

            @Override
            protected Integer doInBackground(String[]... params) {
                return main(params[0]);
            }

            @Override
            protected void onProgressUpdate(Integer... values) {
                if (kitIntenrface != null) {
                    kitIntenrface.onProgress(values[0]);
                }
            }

            @Override
            protected void onPostExecute(Integer integer) {
                if (kitIntenrface != null) {
                    kitIntenrface.onEnd(integer);
                }
            }
        }.execute(commands);
    }


    public native static int main(String[] commands);
    //
    public native static String native_GetFFmpegVersion();
}
