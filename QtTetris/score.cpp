#include "score.h"
#include <math.h>
#include <QDebug>
score::score(QWidget *parent) : QWidget(parent) {
    highScore = 0;
    level = 0;
}

score::~score() {
}
