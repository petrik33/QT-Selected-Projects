#ifndef DIGITALCLOCK_H
#define DIGITALCLOCK_H

//Made by EDITING the example of Digital CLock in QT Manual
//       (NOT COPYING)
//https://doc.qt.io/qt-5/qtwidgets-widgets-digitalclock-example.html

#include <QLCDNumber>
#include <QTimer>
#include <QTime>

class DigitalClock : public QLCDNumber
{
    Q_OBJECT
public:
    DigitalClock(QWidget* parent = nullptr);
    void RestartTime();
    void StopTime();
private:
    QTime time_ = QTime(0,0);
    QTimer* timer;
private slots:
    void showTime();
};

#endif // DIGITALCLOCK_H
