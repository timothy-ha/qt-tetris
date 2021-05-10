#ifndef NUMBER_H
#define NUMBER_H
#include <QWidget>
#include <QTimer>


class number : public QWidget
{
    Q_OBJECT
public:
    explicit number(QWidget *parent = 0);
    ~number();

    void setnum(int n)
    {
        num = n;
    }

    int getnum()
    {
        return num;
    }

    int getHighScore()
    {
        return highscore;
    }
    int setHighScore(int n)
    {
        highscore = n;
        return highscore;
    }
    int level;

protected:
    int highscore;
    int num;
    QTimer *numTimer;
};

#endif // NUMBER_H
