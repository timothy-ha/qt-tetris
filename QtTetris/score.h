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

    void addScore(int score) {
        gameScore += score;
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

    int sethighScore(int n) {
        highScore = n;
        return highScore;
    }

    int level;

protected:
    int highScore;
    int gameScore;
};

#endif // SCORE_H
