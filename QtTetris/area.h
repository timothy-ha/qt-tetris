#ifndef AREA_H
#define AREA_H

#include <QWidget>
#include <QPainter>
#include <QPixmap>

#define WIDTH 30
#define NUM_X 10
#define NUM_Y 20
#define X_SPACE (NUM_X+3+1)
#define Y_SPACE (NUM_Y+4+1)

class AREA : public QWidget
{
    Q_OBJECT

public:
    explicit AREA(QWidget *parent = 0);
    void paintEvent(QPaintEvent *);
    int map[X_SPACE][Y_SPACE];
    int getAreaSp(int, int);
    void clean();
    int eliminate();

    ~AREA();
private:
    QString src[8] = {"",":/Image/1.png",":/Image/L.png" , ":/Image/J.png", ":/Image/T.png", ":/Image/S.png", ":/Image/Z.png", ":/Image/#.png" };
    void reduce(int y = 0);
signals:

public slots:
};

#endif
