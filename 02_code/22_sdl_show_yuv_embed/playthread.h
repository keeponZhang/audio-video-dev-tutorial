#ifndef PLAYTHREAD_H
#define PLAYTHREAD_H

#include <QThread>

class PlayThread  {

private:
    void *_winId;

public:
    explicit PlayThread(void *winId, QObject *parent = nullptr);
    ~PlayThread();
    void run();


signals:

};

#endif // PLAYTHREAD_H
