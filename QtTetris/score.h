#ifndef SCORE_H
#define SCORE_H
#include <QWidget>
#include <QTimer>


class score : public QWidget
{
    Q_OBJECT
public:
    explicit score(QWidget *parent = 0);
    ~score();

    void setScore(int s)
    {
        currScore = s;
    }

    int setHighScore(int n)
    {
        highscore = n;
        return highscore;
    }

    int getScore()
    {
        return currScore;
    }

    int getHighScore()
    {
        return highscore;
    }

    int level;

protected:
    int highscore;
    int currScore;
    QTimer *numTimer;
};

#endif // SCORE_H
