#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QFile>
#include <QThread>
#include <unistd.h>

extern "C" {
// 设备
#include <libavdevice/avdevice.h>
// 格式
#include <libavformat/avformat.h>
// 工具（比如错误处理）
#include <libavutil/avutil.h>
}

#ifdef Q_OS_WIN
    // 格式名称
    #define FMT_NAME "dshow"
    // 设备名称
    #define DEVICE_NAME "audio=线路输入 (3- 魅声T800)"
    // PCM文件名
    #define FILENAME "F:/out.pcm"
#else
    #define FMT_NAME "avfoundation"
    #define DEVICE_NAME ":0"
    #define FILENAME "/Users/keeponzhang/Downloads/study/ffmpeg/code/audio-video-dev-tutorial/02_code/08_record_audio/out.pcm"
#endif
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);

    qDebug() << "MainWindow" << QThread::currentThread();
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_audioButton_clicked() {


    qDebug() << "on_audioButton_clicked" << QThread::currentThread();

    // 获取输入格式对象
   const AVInputFormat *fmt = av_find_input_format(FMT_NAME);
    if (!fmt) {
        qDebug() << "获取输入格式对象失败" << FMT_NAME;
        return;
    }

    // 格式上下文（将来可以利用上下文操作设备）
    AVFormatContext *ctx = nullptr;
    // 打开设备
    int ret = avformat_open_input(&ctx, DEVICE_NAME, fmt, nullptr);
    if (ret < 0) {
        char errbuf[1024];
        av_strerror(ret, errbuf, sizeof (errbuf));
        qDebug() << "打开设备失败" << errbuf;
        return;
    }

    // 文件名
    QFile file(FILENAME);

    // 打开文件
    // WriteOnly：只写模式。如果文件不存在，就创建文件；如果文件存在，就会清空文件内容
    if (!file.open(QFile::WriteOnly)) {
        qDebug() << "文件打开失败" << FILENAME;

        // 关闭设备
        avformat_close_input(&ctx);
        return;
    }

    // 采集的次数
    int count = 100;

    // 数据包
//    AVPacket pkt;
    // 不断采集数据

    AVPacket *pkt = av_packet_alloc();

    while (count > 0  ) {

        if (ret == 0) { // 读取成功
            // 将数据写入文件

            file.write((const char *) pkt->data, pkt->size);
              qDebug() << "将数据写入文件pkt->size="  <<  pkt->size;
            count--;

        } else if (ret == AVERROR(EAGAIN)) { // 资源临时不可用
              qDebug() << "资源临时不可用 error"  << ret;
            continue;
        } else { // 其他错误
            char errbuf[1024];
            av_strerror(ret, errbuf, sizeof (errbuf));
            qDebug() << "av_read_frame error" << errbuf << ret;
            break;
        }
          av_packet_unref(pkt);



        if(av_read_frame(ctx, pkt) != 0){
            sleep(1);
            continue;
        }
//         qDebug() << "将数据写入文件" << FILENAME;
//        // 将数据写入文件
//        file.write((const char *) pkt->data, pkt->size);
//        av_packet_unref(pkt);

    }
   qDebug() << "释放资源" << FILENAME;
    // 释放资源
    // 关闭文件
   av_packet_free(&pkt);

    file.close();

    // 关闭设备
    avformat_close_input(&ctx);
}
