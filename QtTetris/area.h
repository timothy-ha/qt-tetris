#ifndef AREA_H
#define AREA_H

#include <QWidget>
#include <QPainter>
#include <QPixmap>

class AREA : public QWidget
{
    Q_OBJECT

public:
    explicit AREA(QWidget *parent = 0);
    void paintEvent(QPaintEvent *);
    int map[14][25];
    int getAreaSp(int, int);
    void clean();
    int eliminate();
    const int WIDTH = 30;
    const int X_SPACE = 14;
    const int Y_SPACE = 25;

    ~AREA();
private:
    QString src[8] = {"",":/Image/1.png",":/Image/L.png" , ":/Image/J.png", ":/Image/T.png", ":/Image/S.png", ":/Image/Z.png", ":/Image/#.png" };
    void reduce(int y = 0);
signals:

public slots:
};

#endif
