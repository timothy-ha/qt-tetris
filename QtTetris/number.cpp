#include "number.h"
#include <math.h>
#include <QDebug>
number::number(QWidget *parent) : QWidget(parent)
{
  highscore = 0;
  level = 0;
}

number::~number()
{
}

