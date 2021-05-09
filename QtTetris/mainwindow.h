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
    //void paintEvent(QPaintEvent *);
    void keyPressEvent(QKeyEvent *event);

private slots:
    void blockAction(int i2 = 0);
    void scoreCheck();
    void on_pushButton_released();

private:
    Ui::MainWindow* ui;
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
    int collide(int dx, int dy);

    AREA *area;
    number *Number;
    int thesholdscore;
};

#endif
