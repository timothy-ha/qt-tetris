#include "area.h"
using namespace std;

AREA::AREA(QWidget *parent) : QWidget(parent) {
    this->setFixedSize(tetrisWidth * 29, tetrisWidth * 30);
    clean();
}

void AREA::paintEvent(QPaintEvent *) {
    QPainter paint(this);
    QPixmap tilePic;
    for (int i = 3; i < xPlane - 1; i++) {
        for (int j = 4; j < yPlane - 1; j++) {
            if (tetrisMap[i][j]) {
                tilePic.load(tileImages[tetrisMap[i][j]]); //loading tile
                paint.drawPixmap((i - 3) * tetrisWidth, (j - 4) * tetrisWidth, tetrisWidth, tetrisWidth, tilePic);
            }
        }
    }
}

int AREA::getArea(int x, int y) {
    int col = 0;
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            col = (tetrisMap[x + j][y + i] != 0 ? 1 : 0) + col * 2;
    return col;
}

int AREA::tileRemove() {
    int i, removedLine = 0;
    for (int j = yPlane - 2; j >= 4; j--) {
        for (i = 3; i < xPlane - 1; i++)
            if (!tetrisMap[i][j]) break;

        if (i == xPlane - 1) {
            reduce(j++);
            removedLine++;
        }
    }
    return removedLine;
}

void AREA::reduce(int y) {
    for (int j = y; j >= 4; j--)
        for (int i = 3; i < xPlane - 1; i++)
            tetrisMap[i][j] = tetrisMap[i][j - 1];
}

void AREA::clean() {
    for (int i = 0; i < xPlane; i++)
        for (int j = 0; j < yPlane; j++)
            tetrisMap[i][j] = i < 3 || j == yPlane - 1 || i == xPlane - 1;
}

AREA::~AREA() {}
