#ifndef AREA_H
#define AREA_H
#include <QWidget>
#include <QPainter>
#include <QPixmap>
#include <QDebug>

class AREA : public QWidget
{
    Q_OBJECT

public:
    QString tileImages[8] = {"",":/Image/1.png",":/Image/L.png" , ":/Image/J.png", ":/Image/T.png", ":/Image/S.png", ":/Image/Z.png", ":/Image/#.png" };
    AREA(QWidget *parent = 0);
    void paintEvent(QPaintEvent *);
    int tetrisMap[14][25];
    int getAreaSp(int, int);
    void clean();
    int tileRemove();
    ~AREA();

private:
    void reduce(int y = 0);
    const int xPlane = 14;
    const int yPlane = 25;
    const int tetrisWidth = 30;
signals:

public slots:
};

#endif
