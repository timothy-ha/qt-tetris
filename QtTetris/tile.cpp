#include "tile.h"
#include <QDebug>
#include <iostream>
using namespace std;
int WIDTH = 30;

TILE::TILE(QWidget *parent, int k) : QWidget(parent)
{
    this->setFixedSize(WIDTH*4, WIDTH*4);
    tileType = k;
    tileRotate = 0;
    memcpy(sp, gameMap, sizeof(int)*32);
}

TILE::~TILE()
{}

void TILE::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap tilePic;
    tilePic.load(tileImages[tileType]);
    int bp = sp[tileType-1][tileRotate];
    for (int i = 3; i >= 0; i--)
        for (int j = 3; j >= 0; j--, bp >>= 1)
            if (bp & 1) painter.drawPixmap(j*WIDTH, i*WIDTH, WIDTH, WIDTH, tilePic);
}

void TILE::rotate(){
    tileRotate = (tileRotate + 1) % 4;
}

void TILE::rotate_inv(){
    tileRotate = (tileRotate + 3) % 4;
}

void TILE::flip(){
    tileRotate = (tileRotate + 2) % 4;
}

void TILE::changeType(int type){
    tileType = type;
}

int TILE::tileSpec(){
    //spec of tile as we rotate
    return sp[tileType-1][tileRotate];
}

int TILE::getPrefix(){
    int res = 4;
    int bp = sp[tileType-1][tileRotate];
    bp |= bp >> 4;
    bp |= bp >> 8;
    bp &= 15;
    for (; bp; bp >>= 1, res--);
    qDebug() << res <<endl;
    return res;
}


