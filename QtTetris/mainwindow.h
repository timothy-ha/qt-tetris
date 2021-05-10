#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QElapsedTimer>
#include <QMainWindow>
#include <QApplication>
#include <QMouseEvent>
#include <QVector>
#include <QMediaPlaylist>
#include <QMediaPlayer>
#include <tile.h>
#include <area.h>
#include "number.h"

#define WIDTH 30
#define NUM_X 10
#define NUM_Y 20
#define PADDING 5

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    QString next_src[8] = {"",":/Image/1a.png",":/Image/La.png" , ":/Image/Ja.png", ":/Image/Ta.png", ":/Image/Sa.png", ":/Image/Za.png", ":/Image/#a.png" };
    ~MainWindow();

protected:
    void keyPressEvent(QKeyEvent *event);

private slots:
    void move(int a);
    void rotate(int a);
    void hold(bool clear = false);
    void drop(int a);
    void updateNext();
    void updateScores();
    void prepareBlocks();
    void generatePiece();
    void blockAction();

private:
    TILE *tile;
    QTimer *tileTimer;
    QElapsedTimer *elapsedTime;
    QMediaPlaylist *playlist;
    QMediaPlayer *music;
    AREA *area;
    number *Number;
    QVector<int> piece;
    QVector<int> seven_bag;
    Ui::MainWindow* ui;

    void gameLose();
    void gameStart();
    void gameReady();
    void gamePause();
    void createBlock();
    void changeBlock();
    void Timer();
    int collide(int dx, int dy);

    bool held;
    int holdPiece;
    int linesCleared;
    int tiletime;
    int mode;

    int time;
    int old_time = 0;

    enum { lose = 0, start = 1, ready = 2, pause = 3 };
};

#endif
