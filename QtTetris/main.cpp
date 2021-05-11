#include "mainwindow.h"
#include <QApplication>
#include <QMessageBox>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    MainWindow tetris;
    QIcon icon (":/Image/L.png");
    tetris.setWindowIcon(icon);
    tetris.showNormal();
    return a.exec();
}
