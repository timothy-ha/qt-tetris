#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QApplication>
#include <QMouseEvent>
#include <QVector>
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

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    QString next_src[8] = {"",":/Image/1a.png",":/Image/La.png" , ":/Image/Ja.png", ":/Image/Ta.png", ":/Image/Sa.png", ":/Image/Za.png", ":/Image/#a.png" };
    ~MainWindow();

protected:
    //void paintEvent(QPaintEvent *);
    void keyPressEvent(QKeyEvent *event);

private slots:
    void updateNext();
    void updateScores();
    void generatePiece();
    void blockAction();
    void scoreCheck();

private:
    Ui::MainWindow* ui;
    int win_width;
    int win_height;
    int ahh = 0;
    QVector<int> piece;
    void gameLose();
    void gameStart();
    void gameReady();
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
    void changeBlock();
    QTimer *tileTimer;
    int tiletime;
    int collide(int dx, int dy);

    AREA *area;
    number *Number;
    int thesholdscore;
};

#endif
