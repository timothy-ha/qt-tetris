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

    area = new AREA(this);

    for (int i = 0; i < 5; i++) {
        generatePiece( (i == 0) ? true : false );
    }

    updateNext();

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
        if (event->key() == Qt::Key_Escape) {gameLose(); if (Number->getnum() > Number->getHighScore()) Number->setHighScore(Number->getnum()); gameReady(); return;}
        if (event->key() == Qt::Key_Z){
            // rotate first
            tile->rotate();
            int prefix = tile->getPrefix();
            // if at left boundary shift back
            if (tile->pos().x() < (-prefix)*WIDTH)
                tile->move((-prefix)*WIDTH, tile->pos().y());


            tile->update();
        }

        if (event->key() == Qt::Key_X){
            // rotate first
            tile->rotate_inv();
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
            blockAction(); // (block, down) = (0, 1)

        if (event->key() == Qt::Key_L){
            int res = collide(1,0);
            if (!res) tile->move(tile->pos().x() + WIDTH, tile->pos().y());
        }
        if (event->key() == Qt::Key_Enter) gamePause();
        if (event->key() == Qt::Key_Space) {
            int res = collide(0,1);
            while (res != 1) {
                if (!res) blockAction();
                res = collide(0,1);
            }
        }
        break;
    case lose:
        gameReady();
        break;
    case redy:
        if (event->key() == Qt::Key_Escape) {
            close();
        }
        else gameStart();
        break;
    default:
        gameStart();
        break;
    }

}

void MainWindow::createBlock(){
    ahh = 0;
    Number->level = 0;
    thesholdscore = 1000;
    // reset area map
    Number->setnum(0);
    area->clean();
    area->update();
    updateScores();
    tileTimer = new QTimer(this);
    tiletime = 250;
    tile->move(2*WIDTH,-4*WIDTH);
    QSignalMapper* signalMapper = new QSignalMapper (this) ;
    connect(tileTimer, SIGNAL(timeout()), signalMapper, SLOT(map()));
    signalMapper->setMapping(tileTimer, 0 << 1);
    connect(signalMapper, SIGNAL(mapped(int)), this, SLOT(blockAction()));
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

void MainWindow::changeBlock(){
    tile->rot = 0;
    tile->change(piece.at(0));
    piece.pop_front();
    generatePiece();
    int amount = QRandomGenerator64::global()->bounded(2, 4);
    tile->move(amount*WIDTH,-4*WIDTH);
    updateScores();
    updateNext();
}

void MainWindow::generatePiece(bool first) {
    if (first) {
        int a = QRandomGenerator64::global()->bounded(1, 8);
        piece.push_back(a);
    }

    if (seven_bag.size() == 0) {
        for (int i = 0; i < 7; i++) {
            seven_bag.push_back(QRandomGenerator64::global()->bounded(1, 8));
        }
    }
}

void MainWindow::updateNext() {
    ui->label_next->setAlignment(Qt::AlignCenter);

    QPixmap a(next_src[piece.at(0)]);
    ui->next_0->setPixmap(a);
    ui->next_0->setAlignment(Qt::AlignCenter);

    QPixmap b(next_src[piece.at(1)]);
    ui->next_1->setPixmap(b);
    ui->next_1->setAlignment(Qt::AlignCenter);

    QPixmap c(next_src[piece.at(2)]);
    ui->next_2->setPixmap(c);
    ui->next_2->setAlignment(Qt::AlignCenter);

    QPixmap d(next_src[piece.at(3)]);
    ui->next_3->setPixmap(d);
    ui->next_3->setAlignment(Qt::AlignCenter);

    QPixmap e(next_src[piece.at(4)]);
    ui->next_4->setPixmap(e);
    ui->next_4->setAlignment(Qt::AlignCenter);
}

void MainWindow::updateScores() {
    ui->score->setText(QString::number(Number->getnum()));
    ui->high_score->setText(QString::number(Number->getHighScore()));
}


int MainWindow::collide(int dx, int dy){
    // block1 and area
    int x, y;
    x = tile->pos().x()/WIDTH + 3 + dx;
    y = tile->pos().y()/WIDTH + 4 + dy;
    int blksp = tile->getBlockSp(), areasp = area->getAreaSp(x, y);

    return (blksp & areasp) ? 1: 0;
}

void MainWindow::blockAction(){
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
        changeBlock();
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

