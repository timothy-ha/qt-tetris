#include "mainwindow.h"
#include <ctime>
#include <QPainter>
#include <QPixmap>
#include <QSignalMapper>
#include <QMessageBox>
#include <iostream>
#define SMALLEST_TIME 150
using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    win_width = (NUM_X+PADDING)*WIDTH;
    win_height = NUM_Y*WIDTH;
    this->setFixedSize(win_width, win_height);
    qsrand(time(NULL));
    area = new AREA(this);
    int init_block = (qrand() % 7) + 1;
    tile = new TILE(this, init_block);
    Number = new number(this);
    gameRedy();
}

MainWindow::~MainWindow()
{

}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    switch (gamemod) {
    case start:
        if (event->key() == Qt::Key_Escape) {gameLose(); gameRedy(); return;}
        if (event->key() == Qt::Key_W){
            // rotate first
            tile->rotate();
            QPoint original = tile->pos();
            int prefix = tile->getPrefix();
            // if at left boundary shift back
            if (tile->pos().x() < (-prefix)*WIDTH)
                tile->move((-prefix)*WIDTH, tile->pos().y());
            // if collide someone rotate and move bcak
            if (collide(0,0,0)) {
                tile->rotate_inv();
                tile->move(original);
            }

            tile->update();
        }
        if (event->key() == Qt::Key_S)
            blockAction(1); // (block, down) = (0, 1)
        if (event->key() == Qt::Key_A){
            int res = collide(0,-1,0);
            if (!res) tile->move(tile->pos().x() - WIDTH, tile->pos().y());
            else if (res == 2) pushBlock(0, 1, -1, 0);
        }
        if (event->key() == Qt::Key_D){
            int res = collide(0,1,0);
            if (!res) tile->move(tile->pos().x() + WIDTH, tile->pos().y());
            else if (res == 2) pushBlock(0, 1, 1, 0);
        }
        if (event->key() == Qt::Key_Enter) gamePause();
        if (event->key() == Qt::Key_E) {
            int res = collide(0,0,1);
            while (res != 1) {
                if (!res) blockAction(1);
                else pushBlock(0, 1, 0, 1);
                res = collide(0,0,1);
                //cout << res << endl;
            }
        }
        if (event->key() == Qt::Key_Space) {
            int res = collide(1,0,1);
            while (res != 1) {
                if (!res) blockAction(3);
                else pushBlock(1, 0, 0, 1);
                res = collide(1,0,1);
                //cout << res << endl;
            }
        }
        break;
    case lose:
        gameRedy();
        break;
    case redy:
        if (event->key() == Qt::Key_Escape) close();
        else gameStart();
        break;
    default:
        gameStart();
        break;
    }

}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    switch (gamemod) {
    case start:
        gamePause();
        break;
    case lose:
        gameRedy();
        break;
    case redy:
        gameStart();
        break;
    default:
        gameStart();
        break;
    }

}


void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap bgImg[2];
    bgImg[0].load(":/Image/grid4.png");
    bgImg[1].load(":/Image/grid5.png");
    painter.setOpacity(0.8);
    for (int i = 0; i < NUM_X; i++)
        for (int j = 0; j < NUM_Y; j++)
            painter.drawPixmap(i*WIDTH, j*WIDTH, WIDTH, WIDTH, bgImg[(i+j)%2]);
}

void MainWindow::createBlock(){
    Number->level = 0;
    thesholdscore = 1000;
    // reset area map
    Number->setnum(0);
    area->clean();
    area->update();

    tileTimer = new QTimer(this);
    tiletime = 500;
    tile->move((0*NUM_X/2+qrand()%(NUM_X/2-4+1))*WIDTH, -4*WIDTH);
    QSignalMapper* signalMapper = new QSignalMapper (this) ;
    connect(tileTimer, SIGNAL(timeout()), signalMapper, SLOT(map()));
    signalMapper->setMapping(tileTimer, 0 << 1);
    connect(signalMapper, SIGNAL(mapped(int)), this, SLOT(blockAction(int)));
    connect(tileTimer, SIGNAL(timeout()), this, SLOT(scoreCheck()));
}

void MainWindow::scoreCheck(){
    if (tiletime >= SMALLEST_TIME && Number->getnum() >= thesholdscore) {
        thesholdscore += 1000;
        tiletime -= 50;
        tileTimer->stop();
        tileTimer->start(tiletime);

    }
}

void MainWindow::changeBlock(int i){
    int new_block = (qrand() % 7) + 1;
    tile->change(new_block);
    tile->move((i*NUM_X/2+qrand()%(NUM_X/2-4+1))*WIDTH, -4*WIDTH);
}

void MainWindow::pushBlock(int pusher, int pushee, int x, int y){
    if (collide(pushee, x, y) == 1) {blockAction(2*pushee+1); return;}
    else {
        tile->move(tile->pos().x() + x*WIDTH, tile->pos().y() + y*WIDTH);
        tile->move(tile->pos().x() + x*WIDTH, tile->pos().y() + y*WIDTH);
    }
}


int MainWindow::collide(int i, int dx, int dy){
    // block1 and area
    int x, y;
    x = tile->pos().x()/WIDTH + 3 + dx;
    y = tile->pos().y()/WIDTH + 4 + dy;
    int blksp = tile->getBlockSp(), areasp = area->getAreaSp(x, y);

    return (blksp & areasp) ? 1: 0;
}

void MainWindow::blockAction(int i2){
    int i = i2 >> 1;
    // lose
    for (int k = 3; k < X_SPACE-1; k++) if (area->map[k][3]) {
        if (Number->getnum() > Number->getHighScore()) Number->setHighScore(Number->getnum());
        gameLose();
        return;
    }
    // touch bottom
    if (collide(i,0,1) == 1){
        int x, y, blksp = tile->getBlockSp();
        x = tile->pos().x()/WIDTH + 3;
        y = tile->pos().y()/WIDTH + 4;
        // store in area
        for (int k = 3; k >= 0; k--)
            for (int j = 3; j >= 0; j--, blksp >>= 1)
                if (blksp & 1) area->map[x+j][y+k] = tile->kind;
        area->update();

        // judge if some row(s) can be eliminated
        int res = area->eliminate();
        if (res){
            Number->setnum(Number->getnum()+(1<<(res-1))*100);
            // the more row(s) are eliminated, the larger the volumn will be.

        }
        area->update();
        // change the block back to top
        changeBlock(i);
    }
    else tile->move(tile->pos().x(), tile->pos().y() + WIDTH);
}

void MainWindow::gameRedy()
{
    gamemod=redy;
    createBlock();

}

void MainWindow::gameLose()
{
    gamemod=lose;
    tileTimer->stop();

}

void MainWindow::gamePause()
{
    gamemod=pause;
    tileTimer->stop();

}

void MainWindow::gameStart()
{
    gamemod=start;
    tileTimer->start(tiletime);
}
