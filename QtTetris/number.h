#ifndef NUMBER_H
#define NUMBER_H

#include <QWidget>
#include <QTimer>
#define WIDTH 30
#define NUM_X 10
#define NUM_Y 20
#define PADDING 5
#define SCREEN_RIGHT (NUM_X + PADDING) * WIDTH
#define NUM_WIDTH 45
#define NUM_HEIGHT 63

class number : public QWidget
{
    Q_OBJECT
public:
    explicit number(QWidget *parent = 0);
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
    QTimer *numTimer;
    QString numString[10];
};

#endif // NUMBER_H
