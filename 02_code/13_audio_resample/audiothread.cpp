#include "audiothread.h"

#include <QDebug>
#include "ffmpegs.h"

#ifdef Q_OS_WIN
    // 格式名称
    #define FMT_NAME "dshow"
    // 设备名称
    #define DEVICE_NAME "audio=线路输入 (3- 魅声T800)"
    // PCM文件名
    #define FILEPATH "F:/"
#else
    #define FMT_NAME "avfoundation"
    #define DEVICE_NAME ":0"
    #define FILEPATH "/Users/keeponzhang/Downloads/study/ffmpeg/code/audio-video-dev-tutorial/02_code/13_audio_resample/"
#define FILEPATH_FILE1 "/Users/keeponzhang/Downloads/study/ffmpeg/code/audio-video-dev-tutorial/02_code/13_audio_resample/44100_s16le_2.pcm"
#define FILEPATH_FILE2 "/Users/keeponzhang/Downloads/study/ffmpeg/code/audio-video-dev-tutorial/02_code/13_audio_resample/48000_f32le_1.pcm"

#define FILEPATH_FILE3 "/Users/keeponzhang/Downloads/study/ffmpeg/code/audio-video-dev-tutorial/02_code/13_audio_resample/48000_s32le_1.pcm"
#define FILEPATH_FILE4 "/Users/keeponzhang/Downloads/study/ffmpeg/code/audio-video-dev-tutorial/02_code/13_audio_resample/44100_s16le_2_new.pcm"

#endif



AudioThread::AudioThread(QObject *parent) : QThread(parent) {
    // 当监听到线程结束时（finished），就调用deleteLater回收内存
    connect(this, &AudioThread::finished,
            this, &AudioThread::deleteLater);
}

AudioThread::~AudioThread() {
    // 断开所有的连接
    disconnect();
    // 内存回收之前，正常结束线程
    requestInterruption();
    // 安全退出
    quit();
    wait();
    qDebug() << this << "析构（内存被回收）";
}

//void freep(void **ptr) {
//    free(*ptr);
//    *ptr = nullptr;
//}

void AudioThread::run() {
    // 44100_s16le_2 -> 48000_f32le_2 -> 48000_s32le_1 -> 44100_s16le_2
    QString filename = FILEPATH;

    ResampleAudioSpec ras1;
    ras1.filename =FILEPATH_FILE1;
    ras1.sampleFmt = AV_SAMPLE_FMT_S16;
    ras1.sampleRate = 44100;
    ras1.chLayout = AV_CH_LAYOUT_STEREO;

    ResampleAudioSpec ras2;
    ras2.filename =FILEPATH_FILE2;
    ras2.sampleFmt = AV_SAMPLE_FMT_FLT;
    ras2.sampleRate = 48000;
//    单声道
    ras2.chLayout = AV_CH_LAYOUT_MONO;

    ResampleAudioSpec ras3;
    ras3.filename = FILEPATH_FILE3;
    ras3.sampleFmt = AV_SAMPLE_FMT_S32;
    ras3.sampleRate = 48000;
    ras3.chLayout = AV_CH_LAYOUT_MONO;

    ResampleAudioSpec ras4 = ras1;
    ras4.filename = FILEPATH_FILE4;

    FFmpegs::resampleAudio(ras1, ras2);
//    FFmpegs::resampleAudio(ras2, ras3);
//    FFmpegs::resampleAudio(ras3, ras4);
}
