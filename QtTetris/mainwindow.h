#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QApplication>
#include <QMouseEvent>
#include <tile.h>
#include <AREA.h>
#include "number.h"
#define WIDTH 30
#define NUM_X 10
#define NUM_Y 20
#define X_SPACE (NUM_X + 3 + 1)
#define Y_SPACE (NUM_Y + 4 + 1)
#define PADDING 5

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void paintEvent(QPaintEvent *);
    void keyPressEvent(QKeyEvent *event);
    void mousePressEvent(QMouseEvent *event);

private slots:
    void blockAction(int i2 = 0);
    void scoreCheck();

private:
    int win_width;
    int win_height;
    void gameLose();
    void gameStart();
    void gameRedy();
    void gamePause();
    enum
    {
        lose = 0,
        start = 1,
        redy = 2,
        pause = 3
    };

    int gamemod;
    TILE *tile;

    void createBlock();
    void changeBlock(int i = 0);
    QTimer *tileTimer;
    int tiletime;
    int collide(int i, int dx, int dy);
    void pushBlock(int pusher, int pushee, int x, int y);

    AREA *area;
    number *Number;
    int thesholdscore;
};

#endif
