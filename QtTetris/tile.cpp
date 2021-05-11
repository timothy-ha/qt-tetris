#include "tile.h"
#include <QDebug>
#include <iostream>
using namespace std;

TILE::TILE(QWidget *parent, int k) : QWidget(parent)
{
    this->setFixedSize(120, 120);
    tileType = k;
    tileRotate = 0;
    memcpy(sp, map, sizeof(int)*32);
}

void TILE::rotate(){
    tileRotate = (tileRotate + 1) % 4;
}

void TILE::rotateInverse(){
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

void TILE::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap tilePic;
    tilePic.load(tileImages[tileType]);
    int bp = sp[tileType-1][tileRotate];
    for (int i = 3; i >= 0; i--)
        for (int j = 3; j >= 0; j--, bp >>= 1)
            if (bp & 1) painter.drawPixmap(j*30, i*30, 30, 30, tilePic);
}


int TILE::getPrefix(){
    int res = 4;
    int bp = sp[tileType-1][tileRotate];
    bp |= bp >> 4;
    bp |= bp >> 8;
    bp &= 15;
    for (; bp; bp >>= 1, res--);
   // qDebug() << res <<endl;
    return res;
}

TILE::~TILE()
{}


