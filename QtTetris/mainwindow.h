#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "tile.h"
#include "area.h"
#include "score.h"
#include <QElapsedTimer>
#include <QMainWindow>
#include <QApplication>
#include <QMouseEvent>
#include <QVector>
#include <QMediaPlaylist>
#include <QMediaPlayer>
using namespace std;


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);

    ~MainWindow();

protected:
    void keyPressEvent(QKeyEvent *event);

private slots:
    void hold(bool clear = false);
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
    score *Score;
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
    int thesholdscore;
    int tiletime;
    int gamemod;
    int time;
    int old_time = 0;
    const int WIDTH = 30;
    const int X_SPACE = 14;
    const int Y_SPACE = 25;

    QString next_src[8] = {"",":/Image/1a.png",":/Image/La.png" , ":/Image/Ja.png", ":/Image/Ta.png", ":/Image/Sa.png", ":/Image/Za.png", ":/Image/#a.png" };

    enum
    {
        lose = 0,
        start = 1,
        redy = 2,
        pause = 3
    };
};

#endif
