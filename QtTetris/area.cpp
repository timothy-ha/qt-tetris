#include "area.h"
#include <iostream>
using namespace std;

AREA::AREA(QWidget *parent) : QWidget(parent) {
    this->setFixedSize(WIDTH * 29, WIDTH * 30);
    clean();
}

int AREA::getAreaSp(int x, int y) {
    int sp = 0;
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            sp = sp * 2 + (map[x + j][y + i] != 0 ? 1 : 0);
    return sp;
}

void AREA::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    QPixmap pix;
    for (int i = 3; i < X_SPACE - 1; i++) {
        for (int j = 4; j < Y_SPACE - 1; j++) {
            if (map[i][j]) {
                pix.load(src[map[i][j]]);
                painter.drawPixmap((i - 3) * WIDTH, (j - 4) * WIDTH, WIDTH, WIDTH, pix);
            }
        }
    }
}

void AREA::clean() {
    for (int i = 0; i < X_SPACE; i++)
        for (int j = 0; j < Y_SPACE; j++)
            map[i][j] = i < 3 || i == X_SPACE - 1 || j == Y_SPACE - 1;
}

int AREA::eliminate() {
    int i, res = 0;
    for (int j = Y_SPACE - 2; j >= 4; j--) {
        for (i = 3; i < X_SPACE - 1; i++)
            if (!map[i][j]) break;

        if (i == X_SPACE - 1) {
            reduce(j++);
            res++;
        }
    }

    return res;
}

void AREA::reduce(int y) {
    for (int j = y; j >= 4; j--)
        for (int i = 3; i < X_SPACE - 1; i++)
            map[i][j] = map[i][j - 1];
}

AREA::~AREA() {}
