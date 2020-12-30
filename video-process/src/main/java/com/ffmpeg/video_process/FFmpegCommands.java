package com.ffmpeg.video_process;

import java.util.ArrayList;
import java.util.List;

public class FFmpegCommands {

    public static String[] refineAudio(String videoUrl, String outputUrl) {
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
//ffmpeg -i bunny.mp4 -vf drawtext=fontcolor=white:fontsize=40:fontfile=msyh.ttf:line_spacing=7:text='test':x=50:y=50:enable='lte(t\,5)'   -y out.mp4

    public static String[] edit(String videoUrl, String ttf,String outputUrl){

        List<String> strings = new ArrayList<>();

        strings.add("ffmpeg");

        strings.add("-i");
        strings.add(videoUrl);
        strings.add("-vf");
        strings.add("drawtext=fontcolor=white:fontsize=40:fontfile="+ttf+":line_spacing=7:text='test':x=50:y=50:enable='lte(t\\,5)'");

        strings.add("-y");
        strings.add(outputUrl);

        String[] commands = new String[strings.size()];

        for (int i = 0; i < commands.length; i++) {
            commands[i] = strings.get(i);
        }
        return commands;

    }
//drawtext=fontfile=/storage/emulated/0/gluttony/.temp/simsun.ttc:fontsize=30.0:fontcolor=White:x=40:y=1030:text='Look at the jewelry. ':enable=between(t\,0\,4.29)
    public static String[] addSub(String videoUrl, String ttf,String outputUrl) {
        List<String> strings = new ArrayList<>();

        strings.add("ffmpeg");

        strings.add("-i");
        strings.add(videoUrl);

        strings.add("-vf");
//        strings.add("drawtext=fontfile="+ttf+":text='hello world':x=100:y=50:fontsize=24");
        strings.add("drawtext=fontfile=/storage/emulated/0/littleMVer/FreeSerif.ttf:fontsize=24:fontcolor=White:x=10:y=10:text='Look at the jewelry.'");

//        strings.add("-b:v");
//        strings.add("1024k");

        strings.add("-y");
        strings.add(outputUrl);

        String[] commands = new String[strings.size()];

        for (int i = 0; i < commands.length; i++) {
            commands[i] = strings.get(i);
        }
        return commands;
    }

    //ffmpeg -f image2 -i /home/ttwang/images/image%d.jpg tt.mp4
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
        strings.add("[1:v]scale=100:-1[img1];[2:v]scale=100:-1[img2];[0:v][img1]overlay=10:10[bkg];[bkg][img2]overlay=10:30");

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
