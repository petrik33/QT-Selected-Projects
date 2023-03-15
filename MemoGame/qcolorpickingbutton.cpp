#include "qcolorpickingbutton.h"
#include <QColorDialog>

QColorPickingButton::QColorPickingButton( QWidget* parent )
    : QPushButton(parent)
{
    setStyleSheet( "background-color: black");
    connect( this, SIGNAL(clicked()), this, SLOT(changeColor()) );
}

void QColorPickingButton::updateColor()
{
    setStyleSheet( "background-color: " + color.name() );
}

void QColorPickingButton::changeColor()
{
    QColor newColor = QColorDialog::getColor(color, parentWidget());
    if ( newColor != color )
    {
        setColor( newColor );
    }
}

void QColorPickingButton::setColor( const QColor& color )
{
    this->color = color;
    updateColor();
}

const QColor& QColorPickingButton::getColor() const
{
    return color;
}
