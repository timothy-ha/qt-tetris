#include "area.h"
using namespace std;

AREA::AREA(QWidget *parent) : QWidget(parent) {
    this->setFixedSize(tetrisWidth * 29, tetrisWidth * 30);
    clean();
}

int AREA::getAreaSp(int x, int y) {
    int sp = 0;
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            sp = sp * 2 + (tetrisMap[x + j][y + i] != 0 ? 1 : 0);
    return sp;
}

void AREA::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    QPixmap tilePic;
    for (int i = 3; i < xPlane - 1; i++) {
        for (int j = 4; j < yPlane - 1; j++) {
            if (tetrisMap[i][j]) {
                tilePic.load(tileImages[tetrisMap[i][j]]);
                painter.drawPixmap((i - 3) * tetrisWidth, (j - 4) * tetrisWidth, tetrisWidth, tetrisWidth, tilePic);
            }
        }
    }
}

int AREA::tileRemove() {
    int i, res = 0;
    for (int j = yPlane - 2; j >= 4; j--) {
        for (i = 3; i < xPlane - 1; i++)
            if (!tetrisMap[i][j]) break;

        if (i == xPlane - 1) {
            reduce(j++);
            res++;
        }
    }
    return res;
}

void AREA::reduce(int y) {
    for (int j = y; j >= 4; j--)
        for (int i = 3; i < xPlane - 1; i++)
            tetrisMap[i][j] = tetrisMap[i][j - 1];
}

void AREA::clean() {
    for (int i = 0; i < xPlane; i++)
        for (int j = 0; j < yPlane; j++)
            tetrisMap[i][j] = i < 3 || i == xPlane - 1 || j == yPlane - 1;
}

AREA::~AREA() {}
