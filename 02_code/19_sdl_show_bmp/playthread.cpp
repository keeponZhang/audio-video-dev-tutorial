#include "playthread.h"

#include <SDL2/SDL.h>
#include <QDebug>
#include <QFile>
extern "C" {
#include <libavutil/avutil.h>
#include <libswresample/swresample.h>
}
//        #会自动在左边加双引号，右边加双引号
#define END(judge, func) \
    if (judge) { \
        qDebug() << #func << "error" << SDL_GetError(); \
        goto end; \
    }

PlayThread::PlayThread(QObject *parent) {


}

PlayThread::~PlayThread() {


    qDebug() << this << "析构了";
}

void PlayThread::run() {
      qDebug() << "PlayThread  run" ;

    // 像素数据
    SDL_Surface *surface = nullptr;

    // 窗口
    SDL_Window *window = nullptr;

    // 渲染上下文
    SDL_Renderer *renderer = nullptr;

    // 纹理（直接跟特定驱动程序相关的像素数据）
    SDL_Texture *texture = nullptr;

    // 矩形框
    SDL_Rect srcRect = {0, 0, 512, 512};
//    SDL_Rect dstRect = {200, 200, 100, 100};
//    后面两个参数是宽高
    SDL_Rect dstRect = {100, 100, 100, 100};

    SDL_Rect rect;
  qDebug() << "SDL_Rect rect" ;
  qDebug() << "准备SDL_Init" ;
  //      int ret= SDL_Init(SDL_INIT_VIDEO);
    // 初始化子系统
    END(SDL_Init(SDL_INIT_VIDEO), SDL_Init);
           qDebug() << "SDL_Init";

    // 加载BMP
    surface = SDL_LoadBMP("/Users/keeponzhang/Downloads/study/ffmpeg/code/audio-video-dev-tutorial/02_code/19_sdl_show_bmp/in.bmp");
    END(!surface, SDL_LoadBMP);
    qDebug() << "PlayThread  surface" ;
    // 创建窗口
    window = SDL_CreateWindow(
                 // 标题
                 "SDL显示BMP图片",
                 // x
                 SDL_WINDOWPOS_UNDEFINED,
                 // y
                 SDL_WINDOWPOS_UNDEFINED,
                 // w
                 surface->w,
                 // h
                 surface->h,
                 SDL_WINDOW_SHOWN
             );
    qDebug() << " surface->w=" <<  surface->w;
    qDebug() << " surface->h=" << surface->h;

    END(!window, SDL_CreateWindow);

    // 创建渲染上下文
    renderer = SDL_CreateRenderer(window, -1,
                                  SDL_RENDERER_ACCELERATED |
                                  SDL_RENDERER_PRESENTVSYNC);
    if (!renderer) {
        renderer = SDL_CreateRenderer(window, -1, 0);
        END(!renderer, SDL_CreateRenderer);
    }

    // 创建纹理(将surface变成textSure)
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    END(!texture, SDL_CreateTextureFromSurface);



    // 设置绘制颜色（画笔颜色）(只是设置画笔颜色是不起作用的，需要调用SDL_RenderClear)
    END(SDL_SetRenderDrawColor(renderer,
                               255, 255, 0, SDL_ALPHA_OPAQUE),
        SDL_SetRenderDrawColor);

    // 用绘制颜色（画笔颜色）清除渲染目标
    END(SDL_RenderClear(renderer),
        SDL_RenderClear);

    // 画一个红色的矩形框（这个需要放在下面，不然会被绘制背景时覆盖掉）
    END(SDL_SetRenderDrawColor(renderer,
                               255, 0, 0, SDL_ALPHA_OPAQUE),
        SDL_SetRenderDrawColor);
    rect = {0, 0, 50, 50};
    END(SDL_RenderFillRect(renderer, &rect),
        SDL_RenderFillRect);

    // 拷贝纹理数据到渲染目标（默认是window）
//    END(SDL_RenderCopy(renderer, texture, &srcRect, &dstRect),
//        SDL_RenderCopy);

    // 更新所有的渲染操作到屏幕上
    SDL_RenderPresent(renderer);

//    SDL_Delay(500);

end:
      qDebug()  << "end -----";
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
//    SDL_DestroyWindow(window);
//    SDL_Quit();
}
