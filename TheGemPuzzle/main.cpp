#include "mainwindow.h"
#include <QApplication>
#include "digitalclock.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    DigitalClock gameClock;
    w.show();
    return a.exec();
}
