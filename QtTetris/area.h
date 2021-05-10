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
    void clean();
    int map[34][25];
    int getAreaSp(int, int);
    int eliminate();
    int X_SPACE = 34;
    int Y_SPACE = 25;
    int WIDTH =  30;
    ~AREA();
private:
    QString src[8] = {"",":/Image/1.png",":/Image/L.png" , ":/Image/J.png", ":/Image/T.png", ":/Image/S.png", ":/Image/Z.png", ":/Image/#.png" };
    void reduce(int y = 0);
signals:

public slots:
};

#endif
