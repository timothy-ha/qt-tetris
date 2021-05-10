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

    QString src[8] = {"",":/Image/1.png",":/Image/L.png" , ":/Image/J.png", ":/Image/T.png", ":/Image/S.png", ":/Image/Z.png", ":/Image/#.png" };

    void paintEvent(QPaintEvent *);
    void rotate();
    void rotate_inv();
    void change(int k = 0);

    int kind;
    int rot;
    int sp[8][4];
    int getPrefix();
    int getBlockSp();


private:
signals:
public slots:
};
#endif
