
#include "ui_mainwindow.h"
#include "mainwindow.h"
#include <ctime>
#include <QDebug>
#include <QPainter>
#include <QPixmap>
#include <QSignalMapper>
#include <QRandomGenerator64>
#include <QMessageBox>
#include <iostream>
#define SMALLEST_TIME 150
using namespace std;


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //win_width = (NUM_X+PADDING)*WIDTH;
    //win_height = NUM_Y*WIDTH;
    //this->setFixedSize(win_width, win_height);
    //qsrand(time(NULL));

    area = new AREA(this);

    for (int i = 0; i < 7; i++) {
        generatePiece();
    }

    tile = new TILE(this, piece.at(0));
    piece.pop_front();
    generatePiece();

    Number = new number(this);
    gameReady();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    switch (gamemod) {
    case start:
        if (event->key() == Qt::Key_Escape) {gameLose(); gameReady(); return;}
        if (event->key() == Qt::Key_Z){
            // rotate first
            tile->rotate();
            QPoint original = tile->pos();
            int prefix = tile->getPrefix();
            // if at left boundary shift back
            if (tile->pos().x() < (-prefix)*WIDTH)
                tile->move((-prefix)*WIDTH, tile->pos().y());


            tile->update();
        }

        if (event->key() == Qt::Key_X){
            // rotate first
            tile->rotate_inv();
            QPoint original = tile->pos();
            int prefix = tile->getPrefix();
            // if at left boundary shift back
            if (tile->pos().x() < (-prefix)*WIDTH)
                tile->move((-prefix)*WIDTH, tile->pos().y());

            tile->update();
        }

        if (event->key() == Qt::Key_J){
            int res = collide(-1,0);
            if (!res) tile->move(tile->pos().x() - WIDTH, tile->pos().y());
        }

        if (event->key() == Qt::Key_K)
            blockAction(1); // (block, down) = (0, 1)

        if (event->key() == Qt::Key_L){
            int res = collide(1,0);
            if (!res) tile->move(tile->pos().x() + WIDTH, tile->pos().y());
        }
        if (event->key() == Qt::Key_Enter) gamePause();
        if (event->key() == Qt::Key_Space) {
            int res = collide(0,1);
            while (res != 1) {
                if (!res) blockAction(3);
                res = collide(0,1);
            }
        }
        break;
    case lose:
        gameReady();
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

void MainWindow::createBlock(){
    Number->level = 0;
    thesholdscore = 1000;
    // reset area map
    Number->setnum(0);
    area->clean();
    area->update();

    tileTimer = new QTimer(this);
    tiletime = 250;
    tile->move(2*WIDTH,-4*WIDTH);
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
    //int new_block = QRandomGenerator64::global()->bounded(1, 7);
    tile->change(piece.at(0));
    piece.pop_front();
    generatePiece();
    int amount = QRandomGenerator64::global()->bounded(2, 4);
    tile->move(amount*WIDTH,-4*WIDTH);

    QPixmap pm(":/Image/1.png");
    ui->next_0->setPixmap(pm);
    ui->next_0->setScaledContents(true);

}

void MainWindow::generatePiece() {
    int a = QRandomGenerator64::global()->bounded(1, 7);
    piece.push_back(a);
}


int MainWindow::collide(int dx, int dy){
    // block1 and area
    int x, y;
    x = tile->pos().x()/WIDTH + 3 + dx;
    y = tile->pos().y()/WIDTH + 4 + dy;
    int blksp = tile->getBlockSp(), areasp = area->getAreaSp(x, y);

    return (blksp & areasp) ? 1: 0;
}

void MainWindow::blockAction(int i2){
    int i = i2 >> 1;
    //qDebug() << i;
    // lose
    for (int k = 3; k < X_SPACE-1; k++) if (area->map[k][3]) {
        if (Number->getnum() > Number->getHighScore()) Number->setHighScore(Number->getnum());
        gameLose();
        return;
    }
    // touch bottom
    if (collide(0,1) == 1){
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

void MainWindow::gameReady()
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

