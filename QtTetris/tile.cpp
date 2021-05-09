#include "tile.h"
#include <QDebug>
#include <iostream>
using namespace std;
int WIDTH = 30;

TILE::TILE(QWidget *parent, int k) : QWidget(parent)
{
    this->setFixedSize(WIDTH*4, WIDTH*4);
    kind = k;
    rot = 0;
    int map[7][4] = {
        {15,4369,15,4369},
        {23,785,116,547},
        {71,275,113,802},
        {39,305,114,562},
        {54,561,54,561},
        {99,306,99,306},
        {51,51,51,51}
    };
    memcpy(sp, map, sizeof(int)*32);
}

TILE::~TILE()
{}

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

void TILE::rotate(){
    rot = (rot + 1) % 4;
}

void TILE::rotate_inv(){
    rot = (rot + 3) % 4;
}

void TILE::change(int k){
    kind = k;
}

int TILE::getPrefix(){
    int res = 4;
    int bp = sp[kind-1][rot];
    bp |= bp >> 4;
    bp |= bp >> 8;
    bp &= 15;
    for (; bp; bp >>= 1, res--);
    return res;
}

int TILE::getBlockSp(){
    return sp[kind-1][rot];
}
