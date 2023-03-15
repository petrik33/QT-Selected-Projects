#include "digitalclock.h"

DigitalClock::DigitalClock(QWidget *parent)
    : QLCDNumber(parent)
{
    setSegmentStyle(Filled);

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &DigitalClock::showTime);
    timer->start(1000);

    showTime();

//    setWindowTitle(tr("Digital Clock"));
//    resize(150, 60);
}

void DigitalClock::RestartTime(){
    time_ = QTime(0,0);
    timer->start(1000);
    showTime();
}

void DigitalClock::StopTime(){
    timer->stop();
}

void DigitalClock::showTime()
{
    QString text = time_.toString("mm:ss");
    if ((time_.second() % 2) == 1)
        text[2] = ' ';
    display(text);
    time_ = time_.addSecs(1);
}
