#ifndef PLAYTHREAD_H
#define PLAYTHREAD_H

#include <QThread>
#include <SDL2/SDL.h>

class PlayThread  {

private:

    SDL_Texture *createTexture(SDL_Renderer *renderer);
    void showClick(SDL_Event &event,
                   SDL_Renderer *renderer,
                   SDL_Texture *texture);

public:
    explicit PlayThread(QObject *parent = nullptr);
    ~PlayThread();
      void run();

signals:

};

#endif // PLAYTHREAD_H
