#ifndef TETRIS_H
#define TETRIS_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class Tetris; }
QT_END_NAMESPACE

class Tetris : public QMainWindow
{
    Q_OBJECT

public:
    Tetris(QWidget *parent = nullptr);
    ~Tetris();

private:
    Ui::Tetris *ui;
};
#endif // TETRIS_H
