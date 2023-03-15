#include "clock.h"

Clock::Clock(QWidget *parent) : QWidget(parent)
{
    font = QFont("MS Shell Dlg 2");
    currentTime = QTime::currentTime();
    clockTimer = new QTimer(this);
    clockTimer->start();
    clockTimer->setInterval(timeUpdateEachMS);
    connect(clockTimer,SIGNAL(timeout()),this,SLOT(timeUpdate()));
}

QPainter *Clock::setupPainter()
{
    QPainter* painter = new QPainter(this);
    QPen pen;
    pen.setColor(penColor);
    pen.setWidth(penWidth);
    painter->setPen(pen);
    painter->setFont(font);
    QBrush brush(bgColor);
    if(useImageAsBG && bgImage!=nullptr)
    {
        double Dim = qMin(width(),height());
        brush.setTexture(bgImage->scaled(Dim,Dim));
    }
    painter->setBrush(brush);
    return painter;
}

void Clock::paintEvent(QPaintEvent *event)
{
    QPainter* painter = setupPainter();
    double Radius = qMin(width(),height()) / 2 * sizePart;
    double centerX = x() + width()/2;
    double centerY = y() + height()/2;
    QPointF center(centerX,centerY);
    QRectF drawRect(centerX-Radius,centerY-Radius,Radius*2,Radius*2);
    if(shape == Round)
    {
       painter->drawEllipse(drawRect);
    }
    else
    {
        painter->drawRect(drawRect);
    }

    if(clockArrows)
    {

        //Drawing Seconds Arrow

        double measureProgress = currentTime.second();
        double measureLimit = 60;

        if(secondsEnabled)
        {
            double secArrowLen = Radius * 0.75;

            double secArrowDirection = M_PI * (0.5 - (double)2 / measureLimit * measureProgress);
            double secArrowEndX = centerX + cos(secArrowDirection) * secArrowLen;
            double secArrowEndY = centerY - sin(secArrowDirection) * secArrowLen;
            QPointF secArrowEnd(secArrowEndX,secArrowEndY);
            painter->drawLine(center,secArrowEnd);
        }

        //Drawing Minutes Arrow
        double minArrowLen = Radius * 0.5;

        measureProgress += currentTime.minute() * measureLimit;
        measureLimit *= 60;

        double minArrowDirection = M_PI * (0.5 - (double)2 / measureLimit * measureProgress);
        double minArrowEndX = centerX + cos(minArrowDirection) * minArrowLen;
        double minArrowEndY = centerY - sin(minArrowDirection) * minArrowLen;
        QPointF minArrowEnd(minArrowEndX,minArrowEndY);
        painter->drawLine(center,minArrowEnd);

        //Drawing Hours Arrow
        double hrArrowLen = Radius * 0.25;

        measureProgress += (currentTime.hour() % 12) * measureLimit;
        measureLimit *= 12;

        double hrArrowDirection = M_PI * (0.5 - (double)2 / measureLimit * measureProgress);
        double hrArrowEndX = centerX + cos(hrArrowDirection) * hrArrowLen;
        double hrArrowEndY = centerY - sin(hrArrowDirection) * hrArrowLen;
        QPointF hrArrowEnd(hrArrowEndX,hrArrowEndY);
        painter->drawLine(center,hrArrowEnd);

        //Drawing Numbers

        double digitSize = Radius * 0.1 / 2;
        double digitDist = Radius * 0.9;

        for(double i = 1; i <= 12; i++)
        {
            double dir = M_PI * (0.5 - double(i / (double)6));
            QString text;
            switch (digitsType) {
            default:
            case Arabic:
                text = QString::number(i);
                break;
            case Roman:
                text = RomanDigits[i-1];
                break;
            }

            double dx = centerX + cos(dir) * digitDist;
            double dy = centerY - sin(dir) * digitDist;

            QRectF drawBox(dx-digitSize,dy-digitSize,dx+digitSize,dy+digitSize);

            painter->drawText(drawBox,text);

        }
    }
    else
    {
        QString format = "hh:mm";
        if(secondsEnabled) format+=":ss";
        QString timeStr = currentTime.toString(format);
        double textSize = Radius * 0.8;
        QRectF textRect(centerX-textSize,centerY-textSize,textSize*2,textSize*2);
        painter->drawText(textRect,Qt::AlignCenter,timeStr);
    }

    painter->end();
}

void Clock::timeUpdate()
{
    currentTime = currentTime.addMSecs(timeUpdateEachMS*clockSpeed);
    update();
}
