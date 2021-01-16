package com.ffmpeg.video_process;

import java.util.ArrayList;
import java.util.List;

import androidx.annotation.NonNull;

public class FFmpegCommands {

    FFmpegCommands() {
        throw new RuntimeException("Stub!");
    }

    /**
     * Extracting audio
     *
     * @param videoUrl
     * @param outputUrl
     * @return
     */
    public static String[] refineAudio(@NonNull String videoUrl, @NonNull String outputUrl) {

        String[] commands = new String[8];
        commands[0] = "ffmpeg";

        commands[1] = "-i";
        commands[2] = videoUrl;

        commands[3] = "-vn";

        commands[4] = "-y";

        commands[5] = "-acodec";

        commands[6] = "copy";

        commands[7] = outputUrl;
        return commands;
    }

    /**
     * Extracting image
     *
     * @param videoUrl
     * @param outputUrl
     * @return
     */
    public static String[] refineImage(@NonNull String videoUrl, @NonNull String outputUrl) {

        String[] commands = new String[7];
        commands[0] = "ffmpeg";

        commands[1] = "-i";
        commands[2] = videoUrl;

        commands[3] = "-vf";
        commands[4] = "fps=1";

        commands[5] = "-y";
        commands[6] = outputUrl;
        return commands;
    }

    /**
     * Multiple pictures with music composite video
     *
     * @param image
     * @param audio
     * @param outputUrl
     * @return
     */
    public static String[] imageToVideo(@NonNull String image, @NonNull String audio,
                                        @NonNull String outputUrl) {

        List<String> strings = new ArrayList<>();

        strings.add("ffmpeg");

        strings.add("-framerate");
        strings.add("10");

        strings.add("-i");
        strings.add(image);

        strings.add("-i");
        strings.add(audio);

        strings.add("-absf");
        strings.add("aac_adtstoasc");

        strings.add("-b");
        strings.add("1500k");

        strings.add("-vf");
        strings.add("setpts=5.0*PTS");

        strings.add(outputUrl);

        String[] commands = new String[strings.size()];

        for (int i = 0; i < commands.length; i++) {
            commands[i] = strings.get(i);
        }
        return commands;
    }

    public static String[] addImageMark(String appNameImage, String iconImage, String videoUrl,
                                        String outputUrl) {

        List<String> strings = new ArrayList<>();

        strings.add("ffmpeg");

        strings.add("-i");
        strings.add(videoUrl);

        strings.add("-i");
        strings.add(appNameImage);

        strings.add("-i");
        strings.add(iconImage);

        strings.add("-filter_complex");
        strings.add("[1:v]scale=100:-1[img1];[2:v]scale=100:-1[img2];" +
                "[0:v][img1]overlay=10:10[bkg];[bkg][img2]overlay=10:30");

        strings.add("-b:v");
        strings.add("1024k");

        strings.add("-y");
        strings.add(outputUrl);

        String[] commands = new String[strings.size()];

        for (int i = 0; i < commands.length; i++) {
            commands[i] = strings.get(i);
        }
        return commands;
    }

}
