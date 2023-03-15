#ifndef QCOLORPICKINGBUTTON_H
#define QCOLORPICKINGBUTTON_H

#include <QPushButton>
#include <QColor>

class QColorPickingButton : public QPushButton
{
    Q_OBJECT
public:
    QColorPickingButton( QWidget* parent );

    void setColor( const QColor& color );
    const QColor& getColor() const;

public slots:
    void updateColor();
    void changeColor();

private:
    QColor color = Qt::black;
};

#endif // QCOLORPICKINGBUTTON_H
