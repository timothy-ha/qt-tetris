#include "ui_mainwindow.h"
#include "mainwindow.h"
#include <QSignalMapper>
#include <QRandomGenerator64>
#include <QMessageBox>
#include <QSound>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QDebug>
#include <QDateTime>
#include <QElapsedTimer>
#include <QFontDatabase>
#include <QPainter>
#include <QPixmap>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QFontDatabase::addApplicationFont(":/Fonts/Roboto-Regular.ttf");
    QFontDatabase::addApplicationFont(":/Fonts/Roboto-Bold.ttf");
    QFont bold = QFont("Roboto", 13, QFont::Bold);
    QFont font = QFont("Roboto", 13, 1);

    QPalette palette = ui->label_level->palette();
    palette.setColor(ui->label_level->foregroundRole(), Qt::blue);

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

    pTiles();
    updateNext();

    tile = new TILE(this, piece.at(0));
    piece.pop_front();
    gTile();

    Score = new score(this);
    gameReady();
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *event) {
    switch (mode) { //keyboard input
        case start:
            if (event->key() == Qt::Key_Escape) {
                gameLose();
                gameReady();
                return;
            }

            if (event->key() == Qt::Key_Z) rotate(1);

            if (event->key() == Qt::Key_X) rotate(2);

            if (event->key() == Qt::Key_J) move(-1);

            if (event->key() == Qt::Key_Left) move(-1);

            if (event->key() == Qt::Key_K) drop(0);

            if (event->key() == Qt::Key_Down) drop(0);

            if (event->key() == Qt::Key_L) move(1);

            if (event->key() == Qt::Key_Right) move(1);

            if (event->key() == Qt::Key_I) rotate(0);

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

        case ready:
            if (event->key() == Qt::Key_Escape) close();
            else gameStart();
            break;

        default:
            gameStart();
            break;
        }
}

void MainWindow::move(int a) {
    int res = tileCollide(a,0);
    if (!res) {
        QSound::play(":/Sounds/se_game_move.wav");
        tile->move(tile->pos().x() + tetrisWidth * a, tile->pos().y());
    }
}

void MainWindow::rotate(int a) {
    if (a == 0) tile->flip();
    else if (a == 1) tile->rotate();
    else if (a == 2) tile->rotate_inv();

    QPoint original = tile->pos();
    int prefix = tile->getPrefix();
    // revert

    if (tile->pos().x() < (-prefix)*tetrisWidth) tile->move((-prefix)*tetrisWidth, tile->pos().y()); // if tileCollide with block revert

    if (tileCollide(0,0)) {
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
                holdPiece = tile->tileType;
                changeTile();
            } else {
                (tile->tileType == 1) ? tile->move(3*tetrisWidth,-4*tetrisWidth) : tile->move(2*tetrisWidth,-4*tetrisWidth);
                int temp = holdPiece;
                holdPiece = tile->tileType;
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
            QSound::play(":/Sounds/se_game_softdrop.wav"); //sound
            tileMove(); // (block, down) = (0, 1)
            Score->addScore(1);
            break;
        case 1:
            int a = tile->pos().y()/30;
            int res = tileCollide(0,1);
            if (!res)  QSound::play(":/Sounds/se_game_harddrop.wav");

            while (res != 1) {
                if (!res) {
                    tileMove();
                }
                res = tileCollide(0,1);
            }

            int b = tile->pos().y()/30;
            int dist = b - a;

            Score->addScore(dist * 2);
    }
}

void MainWindow::pTiles() {
    seven_bag.clear();
    piece.clear();
    for (int i = 0; i < 5; i++) {
        gTile();
    }
}

void MainWindow::createTile() {
    Score->level = 1;
    Score->resetScore();
    area->clean();
    area->update();
    updateScores();
    tileTimer = new QTimer(this);
    tiletime = 500;
    (tile->tileType == 1) ? tile->move(3*tetrisWidth,-4*tetrisWidth) : tile->move(2*tetrisWidth,-4*tetrisWidth);
    timer();
}


void MainWindow::timer() {
    QSignalMapper* signalMapper = new QSignalMapper (this) ;
    connect(tileTimer, SIGNAL(timeout()), signalMapper, SLOT(map()));
    signalMapper->setMapping(tileTimer, 0 << 1);
    connect(signalMapper, SIGNAL(mapped(int)), this, SLOT(tileMove()));
}

void MainWindow::changeTile() {
    held = false;
    tile->rot = 0;
    tile->change(piece.at(0));
    piece.pop_front();
    gTile();
    (tile->tileType == 1) ? tile->move(3*tetrisWidth,-4*tetrisWidth) : tile->move(2*tetrisWidth,-4*tetrisWidth);
    updateScores();
    updateNext();
}

void MainWindow::gTile() {
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
    ui->level->setText(QString::number(Score->level));
    ui->score->setText(QString::number(Score->getScore()));
    ui->best->setText(QString::number(Score->gethighScore()));
}


int MainWindow::tileCollide(int dx, int dy){
    // block1 and area
    int x, y;
    x = tile->pos().x()/tetrisWidth + 3 + dx;
    y = tile->pos().y()/tetrisWidth + 4 + dy;
    int blksp = tile->getBlockSp(), areasp = area->getAreaSp(x, y);
    return (blksp & areasp) ? 1: 0;
}

void MainWindow::tileMove() {
    time = (int)(elapsedTime->nsecsElapsed()/1e9) + old_time;
    QString time_format = QDateTime::fromTime_t(time).toUTC().toString("hh:mm:ss");

    ui->time->setText(time_format);


    for (int k = 3; k < xPlane-1; k++) if (area->map[k][3]) {
        if (Score->getScore() > Score->gethighScore()) Score->sethighScore(Score->getScore());
        gameLose();
        return;
    }

    if (tileCollide(0,1) == 1) {
        int x, y, blksp = tile->getBlockSp();
        x = tile->pos().x()/tetrisWidth + 3;
        y = tile->pos().y()/tetrisWidth + 4;

        for (int k = 3; k >= 0; k--)
            for (int j = 3; j >= 0; j--, blksp >>= 1)
                if (blksp & 1) area->map[x+j][y+k] = tile->tileType;
         area->update();

        int res = area->tileRemove();

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
                    Score->addScore(100*Score->level);
                    break;

                case 2:
                    Score->addScore(300*Score->level);
                    break;

                case 3:
                    Score->addScore(500*Score->level);
                    break;

                case 4:
                    Score->addScore(800*Score->level);
                    break;
            }
        }
        area->update();
        changeTile();
    }
    else tile->move(tile->pos().x(), tile->pos().y() + tetrisWidth);

    ui->lines->setText(QString::number(linesCleared));
}

void MainWindow::gameReady() {
    held = false;
    hold(true);
    linesCleared = 0;
    mode=ready;
    createTile();
    elapsedTime->start();
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

void MainWindow::gamePause() {
    mode = pause;
    tileTimer->stop();
    music->pause();
}

void MainWindow::gameLose() {
    music->stop();

    QSound::play(":/Sounds/me_game_gameover.wav");
    if (Score->getScore() > Score->gethighScore()) Score->sethighScore(Score->getScore());

    pTiles();
    tile->change(piece.at(0));
    updateNext();
    piece.pop_front();
    gTile();
    mode = lose;
    tileTimer->stop();

    QMessageBox::information(
        nullptr,
        "qt-tetris",
        QString("Game Over.\nScore: %1")
            .arg(ui->score->text())
    );
}





