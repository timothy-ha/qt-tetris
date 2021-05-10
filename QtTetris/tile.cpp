#include "tile.h"
#include <QDebug>
#include <iostream>

TILE::TILE(QWidget *parent, int k) : QWidget(parent)
{
    this->setFixedSize(WIDTH*4, WIDTH*4);
    type = k;
    rot = 0;
    memcpy(sp, map, sizeof(int)*32);
}

TILE::~TILE()
{}

<<<<<<< HEAD
void TILE::paintEvent(QPaintEvent *)
{

    QPainter painter(this);
    QPixmap pix;
    pix.load(src[type]);
    int bp = sp[type-1][rot];
    for (int i = 3; i >= 0; i--)
        for (int j = 3; j >= 0; j--, bp >>= 1)
            if (bp & 1) painter.drawPixmap(j*WIDTH, i*WIDTH, WIDTH, WIDTH, pix);
}

=======
>>>>>>> 80b461dbdb284b8dabbdab65722f8c78ed824f1b
void TILE::rotate(){
    rot = (rot + 1) % 4;
}

void TILE::rotate_inv(){
    rot = (rot + 3) % 4;
}

void TILE::flip(){
    rot = (rot + 2) % 4;
}

void TILE::change(int k){
    type = k;
}

int TILE::getBlockSp(){
    return sp[kind-1][rot];
}

void TILE::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(src[kind]);
    int bp = sp[kind-1][rot];
    for (int i = 3; i >= 0; i--)
        for (int j = 3; j >= 0; j--, bp >>= 1)
            if (bp & 1) painter.drawPixmap(j*WIDTH, i*WIDTH, WIDTH, WIDTH, pix);
}

int TILE::getPrefix(){
    int res = 4;
    int bp = sp[type-1][rot];
    bp |= bp >> 4;
    bp |= bp >> 8;
    bp &= 15;
    for (; bp; bp >>= 1, res--);
    return res;
}

<<<<<<< HEAD
int TILE::getBlockSp(){
    return sp[type-1][rot];
}
=======

>>>>>>> 80b461dbdb284b8dabbdab65722f8c78ed824f1b
