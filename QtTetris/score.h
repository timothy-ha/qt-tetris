#ifndef SCORE_H
#define SCORE_H
#include <QWidget>
#include <QTimer>
#include <QDebug>

class score : public QWidget
{
    Q_OBJECT
public:
    explicit score(QWidget *parent = 0);
    ~score();

    int level;

    void addScore(int score) {
        gameScore += score;
    }

    int sethighScore(int n) {
        highScore = n;
        return highScore;
    }

    void resetScore() {
        gameScore = 0;
    }

    int getScore() {
        return gameScore;
    }

    int gethighScore() {
        return highScore;
    }

protected:
    int highScore;
    int gameScore;
};

#endif // SCORE_H
