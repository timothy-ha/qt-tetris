#include "ui_mainwindow.h"
#include "mainwindow.h"
<<<<<<< HEAD
=======
#include <QMessageBox>
#include <QSound>
#include <QSoundEffect>
#include <QMediaPlayer>
#include <QMediaPlaylist>
>>>>>>> 80b461dbdb284b8dabbdab65722f8c78ed824f1b
#include <QDebug>
#include <QDateTime>
#include <QElapsedTimer>
#include <QFontDatabase>
#include <QPainter>
#include <QPixmap>
#include <QSignalMapper>
#include <QRandomGenerator64>
<<<<<<< HEAD
#include <QMessageBox>
#include <QSound>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <iostream>
#define SMALLEST_TIME 150
using namespace std;
=======

>>>>>>> 80b461dbdb284b8dabbdab65722f8c78ed824f1b

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QFontDatabase::addApplicationFont(":/Fonts/Roboto-Regular.ttf");
    QFontDatabase::addApplicationFont(":/Fonts/Roboto-Bold.ttf");
    QFont bold = QFont("Roboto", 13, QFont::Bold);
    QFont font = QFont("Roboto", 13, 1);
<<<<<<< HEAD

=======
>>>>>>> 80b461dbdb284b8dabbdab65722f8c78ed824f1b
    QPalette palette = ui->label_level->palette();
    palette.setColor(ui->label_level->foregroundRole(), Qt::black);

    ui->label_next->setPalette(palette);
    ui->label_next->setFont(bold);
    ui->label_next->setAlignment(Qt::AlignCenter);

    ui->label_score->setPalette(palette);
    ui->label_score->setFont(bold);
    ui->label_score->setAlignment(Qt::AlignCenter);

    ui->score->setPalette(palette);
    ui->score->setFont(font);
    ui->score->setAlignment(Qt::AlignCenter);

    ui->label_best->setPalette(palette);
    ui->label_best->setFont(bold);
    ui->label_best->setAlignment(Qt::AlignCenter);

    ui->best->setPalette(palette);
    ui->best->setFont(font);
    ui->best->setAlignment(Qt::AlignCenter);

    ui->label_lines->setPalette(palette);
    ui->label_lines->setFont(bold);
    ui->label_lines->setAlignment(Qt::AlignCenter);

    ui->lines->setPalette(palette);
    ui->lines->setFont(font);
    ui->lines->setAlignment(Qt::AlignCenter);

    ui->label_level->setPalette(palette);
    ui->label_level->setFont(bold);
    ui->label_level->setAlignment(Qt::AlignCenter);

    ui->level->setPalette(palette);
    ui->level->setFont(font);
    ui->level->setAlignment(Qt::AlignCenter);

    ui->label_time->setPalette(palette);
    ui->label_time->setFont(bold);
    ui->label_time->setAlignment(Qt::AlignCenter);

    ui->time->setPalette(palette);
    ui->time->setFont(font);
    ui->time->setAlignment(Qt::AlignCenter);

    ui->label_hold->setPalette(palette);
    ui->label_hold->setFont(bold);
    ui->label_hold->setAlignment(Qt::AlignCenter);

    elapsedTime = new QElapsedTimer();
    area = new AREA(this);
    prepareBlocks();
    updateNext();
    tile = new TILE(this, piece.at(0));
    piece.pop_front();
    generatePiece();
    Score = new score(this);
    gameReady();
}

MainWindow::~MainWindow() {
    delete ui;
}

<<<<<<< HEAD
void MainWindow::keyPressEvent(QKeyEvent *event) {
    switch (mode) {
        case start:
            if (event->key() == Qt::Key_Escape) {
                gameLose();
                gameReady();
                return;
            }

            if (event->key() == Qt::Key_Z) rotate(1);

            if (event->key() == Qt::Key_X) rotate(2);
=======
void MainWindow::keyPressEvent(QKeyEvent *event)
{
    switch (gamemod) {
    case start:
        if (event->key() == Qt::Key_Escape) {
            gameLose();
            gameReady();
            return;
        }
        if (event->key() == Qt::Key_Z){
            QSound::play(":/Sounds/se_game_rotate.wav");

            tile->rotate();
            QPoint original = tile->pos();
            int prefix = tile->getPrefix();
            // if at left boundary shift back
            if (tile->pos().x() < (-prefix)*WIDTH) tile->move((-prefix)*WIDTH, tile->pos().y());
                // if collide someone rotate and move bcak
                if (collide(0,0)) {
                    tile->rotate_inv();
                    tile->move(original);
                }
>>>>>>> 80b461dbdb284b8dabbdab65722f8c78ed824f1b

            if (event->key() == Qt::Key_J) move(-1);

            if (event->key() == Qt::Key_Left) move(-1);

            if (event->key() == Qt::Key_K) drop(0);

            if (event->key() == Qt::Key_Down) drop(0);

            if (event->key() == Qt::Key_L) move(1);

<<<<<<< HEAD
            if (event->key() == Qt::Key_Right) move(1);

            if (event->key() == Qt::Key_I) rotate(0);
=======
        if (event->key() == Qt::Key_K) {
            QSound::play(":/Sounds/se_game_move.wav");
            blockAction(); // (block, down) = (0, 1)
            Score->setScore(Score->getScore() + 1);
        }

        if (event->key() == Qt::Key_Down) {
            QSound::play(":/Sounds/se_game_move.wav");
            blockAction(); // (block, down) = (0, 1)
            Score->setScore(Score->getScore() + 1);
        }
>>>>>>> 80b461dbdb284b8dabbdab65722f8c78ed824f1b

            if (event->key() == Qt::Key_Up) rotate(0);

            if (event->key() == Qt::Key_P) {
                old_time = time;
                gamePause();
            }

            if (event->key() == Qt::Key_Space) drop(1);

            if (event->key() == Qt::Key_Shift) hold();

            break;

        case lose:
            gameReady();
            break;

<<<<<<< HEAD
        case ready:
            if (event->key() == Qt::Key_Escape) close();
            else gameStart();
            break;

        default:
            gameStart();
            break;
=======
            gamePause();
        }

        if (event->key() == Qt::Key_Space) {
            // hard drop
            QSound::play(":/Sounds/se_game_harddrop.wav");
            int a = tile->pos().y()/30;
            Score->setScore(Score->getScore() + 2);
            int res = collide(0,1);
            while (res != 1) {
                if (!res) blockAction();
                res = collide(0,1);
            }

            int b = tile->pos().y()/30;
            int dist = b - a;

            Score->setScore(Score->getScore() + (dist * 2));
>>>>>>> 80b461dbdb284b8dabbdab65722f8c78ed824f1b
        }
}

void MainWindow::move(int a) {
    int res = collide(a,0);
    if (!res) {
        QSound::play(":/Sounds/se_game_move.wav");
        tile->move(tile->pos().x() + WIDTH * a, tile->pos().y());
    }
}

void MainWindow::rotate(int a) {
    if (a == 0) tile->flip();
    else if (a == 1) tile->rotate();
    else if (a == 2) tile->rotate_inv();

    QPoint original = tile->pos();
    int prefix = tile->getPrefix();
    // revert if hit boundary
    if (tile->pos().x() < (-prefix)*WIDTH) tile->move((-prefix)*WIDTH, tile->pos().y());
    // if collide with block revert
    if (collide(0,0)) {
        if (a == 0) tile->flip();
        else if (a == 1) tile->rotate_inv();
        else if (a == 2) tile->rotate();
        tile->move(original);
    } else {
        QSound::play(":/Sounds/se_game_rotate.wav");
    }


    tile->update();
}

void MainWindow::hold(bool clear) {
    if (!clear) {
        if (!held) {
            QSound::play(":/Sounds/se_game_hold.wav");
            if (holdPiece == 0) {
                holdPiece = tile->type;
                changeBlock();
            } else {
                (tile->type == 1) ? tile->move(3*WIDTH,-4*WIDTH) : tile->move(2*WIDTH,-4*WIDTH);
                int temp = holdPiece;
                holdPiece = tile->type;
                tile->change(temp);
            }
            held = true;
        }
    } else {
        holdPiece = 0;
    }

    QPixmap a(next_src[holdPiece]);
    ui->hold->setPixmap(a);
    ui->hold->setAlignment(Qt::AlignCenter);

}

void MainWindow::drop(int a) {
    switch (a) {
        case 0:
            QSound::play(":/Sounds/se_game_softdrop.wav");
            blockAction(); // (block, down) = (0, 1)
            Number->addScore(1);
            break;
        case 1:
            int a = tile->pos().y()/30;
            int res = collide(0,1);
            if (!res)  QSound::play(":/Sounds/se_game_harddrop.wav");

            while (res != 1) {
                if (!res) {
                    blockAction();
                }
                res = collide(0,1);
            }

            int b = tile->pos().y()/30;
            int dist = b - a;

            Number->addScore(dist * 2);
    }
}

void MainWindow::prepareBlocks() {
    seven_bag.clear();
    piece.clear();
    for (int i = 0; i < 5; i++) {
        generatePiece();
    }
}

<<<<<<< HEAD
void MainWindow::createBlock() {
    Number->level = 1;
    // reset area map
    Number->resetScore();
=======
void MainWindow::createBlock(){
    Score->level = 1;

    // reset area map
    Score->setScore(0);
>>>>>>> 80b461dbdb284b8dabbdab65722f8c78ed824f1b
    area->clean();
    area->update();
    updateScores();
    tileTimer = new QTimer(this);
    tiletime = 500;
    (tile->type == 1) ? tile->move(3*WIDTH,-4*WIDTH) : tile->move(2*WIDTH,-4*WIDTH);
    Timer();
}


void MainWindow::Timer() {
    QSignalMapper* signalMapper = new QSignalMapper (this) ;
    connect(tileTimer, SIGNAL(timeout()), signalMapper, SLOT(map()));
    signalMapper->setMapping(tileTimer, 0 << 1);
    connect(signalMapper, SIGNAL(mapped(int)), this, SLOT(blockAction()));
<<<<<<< HEAD
    //connect(tileTimer, SIGNAL(timeout()), this, SLOT(scoreCheck()));
}

void MainWindow::changeBlock() {
=======
}



void MainWindow::changeBlock(){
>>>>>>> 80b461dbdb284b8dabbdab65722f8c78ed824f1b
    held = false;
    tile->rot = 0;
    tile->change(piece.at(0));
    piece.pop_front();
    generatePiece();
    (tile->type == 1) ? tile->move(3*WIDTH,-4*WIDTH) : tile->move(2*WIDTH,-4*WIDTH);
    updateScores();
    updateNext();
}

void MainWindow::generatePiece() {
    if (seven_bag.empty()) {
        for (int i = 1; i <= 7; i++) {
            seven_bag.push_back(i);
        }
    }
    int i = QRandomGenerator64::global()->bounded(0, seven_bag.size());
    piece.push_back(seven_bag.at(i));
    seven_bag.erase(seven_bag.begin() + i);
}

void MainWindow::updateNext() {
    ui->label_next->setAlignment(Qt::AlignCenter);

    QPixmap a(next_src[piece.at(0)]);
    QPixmap b(next_src[piece.at(1)]);
    QPixmap c(next_src[piece.at(2)]);
    QPixmap d(next_src[piece.at(3)]);
    QPixmap e(next_src[piece.at(4)]);

    ui->next_0->setPixmap(a);
    ui->next_0->setAlignment(Qt::AlignCenter);

    ui->next_1->setPixmap(b);
    ui->next_1->setAlignment(Qt::AlignCenter);

    ui->next_2->setPixmap(c);
    ui->next_2->setAlignment(Qt::AlignCenter);

    ui->next_3->setPixmap(d);
    ui->next_3->setAlignment(Qt::AlignCenter);

    ui->next_4->setPixmap(e);
    ui->next_4->setAlignment(Qt::AlignCenter);
}

void MainWindow::updateScores() {
<<<<<<< HEAD
    ui->level->setText(QString::number(Number->level));
    ui->score->setText(QString::number(Number->getScore()));
    ui->best->setText(QString::number(Number->gethighScore()));
=======
    ui->level->setText(QString::number(Score->level));
    ui->score->setText(QString::number(Score->getScore()));
    ui->best->setText(QString::number(Score->getHighScore()));
>>>>>>> 80b461dbdb284b8dabbdab65722f8c78ed824f1b
}


int MainWindow::collide(int dx, int dy){
    // block1 and area
    int x, y;
    x = tile->pos().x()/WIDTH + 3 + dx;
    y = tile->pos().y()/WIDTH + 4 + dy;
    int blksp = tile->getBlockSp(), areasp = area->getAreaSp(x, y);
    return (blksp & areasp) ? 1: 0;
}

void MainWindow::blockAction() {
    time = (int)(elapsedTime->nsecsElapsed()/1e9) + old_time;
    QString time_format = QDateTime::fromTime_t(time).toUTC().toString("hh:mm:ss");

    ui->time->setText(time_format);

    // lose
    for (int k = 3; k < X_SPACE-1; k++) if (area->map[k][3]) {
<<<<<<< HEAD
        if (Number->getScore() > Number->gethighScore()) Number->sethighScore(Number->getScore());
=======
        if (Score->getScore() > Score->getHighScore()) Score->setHighScore(Score->getScore());
>>>>>>> 80b461dbdb284b8dabbdab65722f8c78ed824f1b
        gameLose();

        return;
    }
    // touch bottom

    if (collide(0,1) == 1) {
        int x, y, blksp = tile->getBlockSp();
        x = tile->pos().x()/WIDTH + 3;
        y = tile->pos().y()/WIDTH + 4;
        // store in area
        for (int k = 3; k >= 0; k--)
            for (int j = 3; j >= 0; j--, blksp >>= 1)
                if (blksp & 1) area->map[x+j][y+k] = tile->type;

        area->update();

        // check if rows can be eliminated
        int res = area->eliminate();

        if (res) {
            QSound::play(":/Sounds/me_game_start2.wav");

            linesCleared += res;

            int reqLines = 0;
            int reqTotalLines = 0;

            for (int i = 0; i < 12; i++) {
                if (i % 10 == 0) reqLines += 1;

                reqTotalLines += (reqLines += 2);

                if (linesCleared == reqTotalLines) {
                    Score->level++;
                    tiletime -= 50;
                }
            }


            switch (res) {
                case 1:
<<<<<<< HEAD
                    Number->addScore(100*Number->level);
                    break;

                case 2:
                    Number->addScore(300*Number->level);
                    break;

                case 3:
                    Number->addScore(500*Number->level);
                    break;

                case 4:
                    Number->addScore(800*Number->level);
=======
                    Score->setScore(Score->getScore() + 100*Score->level);
                    break;

                case 2:
                    Score->setScore(Score->getScore() + 300*Score->level);
                    break;

                case 3:
                    Score->setScore(Score->getScore() + 500*Score->level);
                    break;

                case 4:
                    Score->setScore(Score->getScore() + 800*Score->level);
>>>>>>> 80b461dbdb284b8dabbdab65722f8c78ed824f1b
                    break;
            }


        }
        area->update();
        changeBlock();
    }
    else tile->move(tile->pos().x(), tile->pos().y() + WIDTH);
    ui->lines->setText(QString::number(linesCleared));
}

void MainWindow::gameReady() {
    held = false;
    hold(true);
    linesCleared = 0;
    mode=ready;
    createBlock();
    elapsedTime->start();
}

<<<<<<< HEAD
void MainWindow::gameLose() {
    music->stop();
    QSound::play(":/Sounds/me_game_gameover.wav");
    if (Number->getScore() > Number->gethighScore()) Number->sethighScore(Number->getScore());
=======


void MainWindow::gameStart()
{
    gamemod=start;
    updateNext();
    tileTimer->start(tiletime);
    elapsedTime->restart();

    playlist = new QMediaPlaylist();
    playlist->addMedia(QUrl("qrc:/Sounds/uih.wav"));
    playlist->setPlaybackMode(QMediaPlaylist::Loop);

    music = new QMediaPlayer();
    music->setPlaylist(playlist);
    music->play();
    music->setVolume(50);
}


void MainWindow::gamePause()
{
    gamemod=pause;
    tileTimer->stop();
    music->pause();

}

void MainWindow::gameLose()
{
    music->stop();
    QSound::play(":/Sounds/me_game_gameover.wav");
    if (Score->getScore() > Score->getHighScore()) Score->setHighScore(Score->getScore());
>>>>>>> 80b461dbdb284b8dabbdab65722f8c78ed824f1b
    prepareBlocks();
    tile->change(piece.at(0));
    updateNext();
    piece.pop_front();
    generatePiece();
<<<<<<< HEAD

    mode = lose;
=======
    gamemod=lose;
>>>>>>> 80b461dbdb284b8dabbdab65722f8c78ed824f1b
    tileTimer->stop();

    QMessageBox::information(
        nullptr,
        "qt-tetris",
        QString("Game Over.\nScore: %1")
            .arg(ui->score->text())
    );

}
<<<<<<< HEAD

void MainWindow::gamePause() {
    mode = pause;
    tileTimer->stop();
    music->pause();
}

void MainWindow::gameStart() {
    mode = start;
    updateNext();
    tileTimer->start(tiletime);
    elapsedTime->restart();

    playlist = new QMediaPlaylist();
    playlist->addMedia(QUrl("qrc:/Sounds/uih.wav"));
    playlist->setPlaybackMode(QMediaPlaylist::Loop);

    music = new QMediaPlayer();
    music->setPlaylist(playlist);
    music->play();
    music->setVolume(50);
}

=======
>>>>>>> 80b461dbdb284b8dabbdab65722f8c78ed824f1b
