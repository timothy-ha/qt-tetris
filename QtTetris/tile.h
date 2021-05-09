#ifndef TILE_H
#define TILE_H
#include <QWidget>
#include <QPainter>
#include <QPixmap>

class TILE : public QWidget
{
    Q_OBJECT

public:
    explicit TILE(QWidget *parent = 0, int k = 0);
    ~TILE();
    void paintEvent(QPaintEvent *);
    void rotate();
    void rotate_inv();
    void change(int k = 0);
    int getPrefix();
    QString src[8] = {"",":/Image/1.png",":/Image/L.png" , ":/Image/J.png", ":/Image/T.png", ":/Image/S.png", ":/Image/Z.png", ":/Image/#.png" };
    int kind;
    int rot;      // rotate: choose 1st~4th pattern
    int sp[8][4]; // block pattern
    int getBlockSp();


private:
signals:
public slots:
};
#endif // TILE_H
