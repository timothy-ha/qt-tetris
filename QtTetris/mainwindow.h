#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <tile.h>
#include <area.h>
#include "score.h"
#include <QElapsedTimer>
#include <QMainWindow>
#include <QMouseEvent>
#include <QVector>
#include <QMediaPlaylist>
#include <QMediaPlayer>
#include <QSignalMapper>
#include <QRandomGenerator64>
#include <QMessageBox>
#include <QSound>
#include <QDateTime>
#include <QElapsedTimer>
#include <QFontDatabase>
#include <QPainter>
#include <QPixmap>
#include <QDebug>

using namespace std;

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
    void levelThreshold();
    void move(int a);
    void rotate(int a);
    void hold(bool clear = false);
    void drop(int a);
    void updateNext();
    void updateScores();
    void pTiles(); //prepare tiles
    void gTile(); //generate tile
    void tileMove();

private:
    TILE *tile;
    QTimer *tileTimer;
    QElapsedTimer *elapsedTime;
    QMediaPlaylist *playlist;
    QMediaPlayer *music;
    AREA *area;
    score *Score;
    QVector<int> piece;
    QVector<int> seven_bag;
    QVector<int> levelReq;
    Ui::MainWindow* ui;

    void gameLose();
    void gameStart();
    void gameReady();
    void gamePause();
    void createTile();
    void changeTile();
    void timer();

    int tileCollide(int x, int y);
    int holdPiece;
    int linesCleared;
    int tiletime;
    int mode;
    int time;
    int old_time = 0;
    bool held;
    const int xPlane = 14;
    const int yPlane = 25;
    const int tetrisWidth = 30;
    enum { lose = 0, start = 1, ready = 2, pause = 3 };
};

#endif
