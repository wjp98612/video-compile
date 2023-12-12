package com.ffmpeg.media_ability;

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
        commands[4] = "fps=3";

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
    public static String[] imageToVideo(@NonNull String imageUrl,
                                        @NonNull String outputUrl,String seconds) {

        List<String> strings = new ArrayList<>();

        strings.add("ffmpeg");

        strings.add("-framerate");
        strings.add("0.33");

        strings.add("-f");
        strings.add("image2");

        strings.add("-i");
        strings.add(imageUrl);

        strings.add("-r");
        strings.add("30");

        strings.add("-vcodec");
        strings.add("libx264");

        strings.add("-pix_fmt");
        strings.add("yuv420p");

        strings.add("-s");
        strings.add("1080*1920");

        strings.add("-t");
        strings.add(seconds);

        //覆盖输出
        strings.add("-y");//直接覆盖输出文件
        //输出文件
        strings.add(outputUrl);
        String[] commands = new String[strings.size()];
        for(int i=0;i<strings.size();i++){
            commands[i]=strings.get(i);
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
