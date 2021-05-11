#include "tile.h"
using namespace std;

TILE::TILE(QWidget *parent, int type) : QWidget(parent)
{
    this->setFixedSize(120, 120);
    tileType = type;
    tileRotate = 0;
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
    return tileStyle[tileType-1][tileRotate];  //spec of tile as we rotate
}

void TILE::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap tilePic;
    tilePic.load(tileImages[tileType]);
    int bp = tileStyle[tileType-1][tileRotate];

    for (int i = 3; i >= 0; i--) //painting the tiles
        for (int j = 3; j >= 0; j--, bp >>= 1)
            if (bp & 1) painter.drawPixmap(j*30, i*30, 30, 30, tilePic);
}


int TILE::getPrefix(){
    int res = 4;
    int bp = tileStyle[tileType-1][tileRotate];
    bp |= bp >> 4;
    bp |= bp >> 8;
    bp &= 15;
    for (; bp; bp >>= 1, res--);
   // qDebug() << res <<endl;
    return res;
}

TILE::~TILE()
{}


