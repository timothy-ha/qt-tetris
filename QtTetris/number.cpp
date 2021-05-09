#include "number.h"
#include <math.h>
#include <QDebug>
number::number(QWidget *parent) : QWidget(parent)
{
  numTimer = new QTimer(this);
  connect(numTimer, SIGNAL(timeout()), this, SLOT(update()));
  numTimer->start(100);
  highscore = 0;
  level = 0;
}

number::~number()
{
}

void number::paintEvent(QPaintEvent *)
{
  //qDebug() << num;
}
