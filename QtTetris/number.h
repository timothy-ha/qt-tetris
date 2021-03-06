#ifndef NUMBER_H
#define NUMBER_H
#include <QWidget>
#include <QTimer>

class score : public QWidget
{
    Q_OBJECT
public:
    explicit score(QWidget *parent = 0);
    ~number();

    void addScore(int n) {
        score += n;
    }

    void resetScore() {
        score = 0;
    }

    int getScore() {
        return score;
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
    int score;
};

#endif // NUMBER_H
