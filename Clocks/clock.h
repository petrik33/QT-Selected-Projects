#ifndef CLOCK_H
#define CLOCK_H

#include <QWidget>
#include <QTime>
#include <QTimer>
#include <QtMath>
#include <QPainter>
#include <QPaintEvent>

enum ClockShape{Round,Square};
enum DigitsType{Arabic,Roman};

class Clock : public QWidget
{
    Q_OBJECT
protected:
    QTime currentTime;
    QTimer* clockTimer;
    int timeUpdateEachMS = 500;

    QFont font;
    int penWidth = 2;

    bool secondsEnabled = true;

    bool clockArrows = true;

    double sizePart = 0.7;

    const QStringList RomanDigits = {"I","II","III","IV","V","VI","VII","VIII","IX","X","XI","XII"};
    double clockSpeed = 1;

    QPixmap* bgImage = nullptr;
    bool useImageAsBG = false;

    ClockShape shape = Round;
    DigitsType digitsType = Roman;

    QColor penColor = Qt::black;
    QColor bgColor = Qt::gray;

    QPainter *setupPainter();
    virtual void paintEvent(QPaintEvent *event) override;
public:

    explicit Clock(QWidget *parent = nullptr);
    void setFont(QFont font_){
        font = font_;
    }
    void setPenWidth(int width){
        penWidth = width;
    }
    void setClockSizePart(double p){
        if(p > 1 || p < 0.2) return;
        sizePart = p;
    }
    void setClockArrowsEnabled(bool enable){
        clockArrows = enable;
    }
    void setPenColor(QColor color){
        penColor = color;
    }
    void setBGImageFromFile(QString fileName){
        if(bgImage != nullptr) delete bgImage;
        bgImage = new QPixmap(fileName);
    }
    void enableBGImage(bool enable){
        useImageAsBG = enable;
    }
    void enableSecond(bool enable){
        secondsEnabled = enable;
    }
    void setBrushColor(QColor color){
        bgColor = color;
    }
    void setDigitsType(DigitsType type){
        digitsType = type;
    }
    void setShapeType(ClockShape _shape){
        shape = _shape;
    }
signals:

protected slots:
    void timeUpdate();
};

#endif // CLOCK_H
