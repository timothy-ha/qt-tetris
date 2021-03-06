#ifndef TILE_H
#define TILE_H
#include <QWidget>
#include <QPainter>
#include <QPixmap>
#include <QDebug>

class TILE : public QWidget
{
    Q_OBJECT

public:
    explicit TILE(QWidget *parent = 0, int k = 0);
    ~TILE();

    void paintEvent(QPaintEvent *);
    void rotate();
    void rotateInverse();
    void flip();
    void changeType(int k = 0);
    int tileType;
    int tileRotate;
    int getPrefix();
    int tileSpec();

private:
    QString tileImages[8] = {"",":/Image/1.png",":/Image/L.png" , ":/Image/J.png", ":/Image/T.png", ":/Image/S.png", ":/Image/Z.png", ":/Image/#.png" };
    int tileStyle[7][4] = { //how 7 tiles are positioned (in shapes).
        {15,4369,15,4369},
        {23,785,116,547},
        {71,275,113,802},
        {39,305,114,562},
        {54,561,54,561},
        {99,306,99,306},
        {51,51,51,51}
    };
signals:
public slots:
};
#endif
