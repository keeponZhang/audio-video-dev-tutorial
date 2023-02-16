#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "playthread.h"
#include <SDL2/SDL.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);
}

MainWindow::~MainWindow() {
    delete ui;
}
void showVersion() {
    SDL_version version;
    SDL_VERSION(&version);
    qDebug() << version.major << version.minor << version.patch;
}

void MainWindow::on_playButton_clicked() {
    showVersion();
    PlayThread *thread = new PlayThread(this);
    thread->run();
}

