#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "playthread.h"
#include <SDL2/SDL.h>
#include <QDebug>
#include <QFile>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_playButton_clicked() {
    PlayThread *thread = new PlayThread(this);
    thread->run();

}

