#include "score.h"
#include <QDebug>
score::score(QWidget *parent) : QWidget(parent)
{
  highscore = 0;
  level = 0;
}

score::~score()
{
}

