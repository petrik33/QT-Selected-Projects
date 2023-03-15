#include "shapescolorsdialog.h"
#include "ui_shapescolorsdialog.h"

ShapesColorsDialog::ShapesColorsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ShapesColorsDialog)
{
    ui->setupUi(this);
    setItemSize();
    ui->shapesCmBox->addItem(tr("Rectangle"), static_cast<int>(Rectangly));
    ui->shapesCmBox->addItem(tr("Circle"), static_cast<int>(Circle));
    ui->shapesCmBox->addItem(tr("Triangle"), static_cast<int>(Triangle));
    ui->shapesCmBox->addItem(tr("Hexagon"), static_cast<int>(Hexagon));
    ui->shapesCmBox->addItem(tr("Dash"), static_cast<int>(Dash));
    ui->shapesCmBox->addItem(tr("T"), static_cast<int>(Letter_T));
    ui->shapesCmBox->addItem(tr("Square"), static_cast<int>(Square));
}

void ShapesColorsDialog::setItemSize(int _itemSize)
{
    itemSize = _itemSize;
    int botY = ui->shapesCmBox->geometry().y();
    itemY = (8 + botY) / 2;
    itemX = width()/2;
}

ShapesColorsDialog::~ShapesColorsDialog()
{
    delete ui;
}

void ShapesColorsDialog::paintEvent(QPaintEvent *event)
{
    QDialog::paintEvent(event);
    QPainter painter(this);
    QColor color = ui->colorPickingButton->getColor();
    painter.setBrush(QBrush(color,Qt::SolidPattern));
    int itemR = itemSize / 2;
    int x = itemX;
    int y = itemY;
    ElementShape shape = ElementShape(ui->shapesCmBox->currentData().toInt());
    switch (shape)
    {
    case Square:
    painter.drawRect(
                x - itemR,
                y - itemR,
                itemSize,
                itemSize
                );
        break;

    case Rectangly:
    painter.drawRect(
                x - itemR,
                y - itemR/2,
                itemSize,
                itemR
                );
        break;

    case Triangle: {
        QPoint pointArr[3];
        for(int i = 0; i < 3; i++)
        {
            double radAngle = -M_PI / 2 + i * M_PI * 2 / 3;
            QPoint p(x + cos(radAngle) * itemR,y + sin(radAngle) * itemR);
            pointArr[i] = p;
        }
        painter.drawPolygon(pointArr,3);
        break;
    }

    case Dash: {
        painter.drawRoundedRect(
                    x - itemR,
                    y - itemSize/16,
                    itemSize,
                    itemSize/8,
                    2,
                    2
                    );
        break;
    }

    case Letter_T: {
        painter.drawLine(x - itemR,y - itemR,x + itemR,y - itemR);
        painter.drawLine(x,y - itemR,x,y + itemR);
        break;
    }

    case Hexagon: {
        QPoint pointArr[6];
        for(int i = 0; i < 6; i++)
        {
            double radAngle = i * M_PI / 3;
            QPoint p(x + cos(radAngle) * itemR,y + sin(radAngle) * itemR);
            pointArr[i] = p;
        }
        painter.drawPolygon(pointArr,6);
        break;
    }

    case Circle:
    painter.drawEllipse(
                x - itemR,
                y - itemR,
                itemSize,
                itemSize
                );
        break;

    default:

        break;
    }
}

void ShapesColorsDialog::on_colorPickingButton_clicked()
{
    int shapeChanged = ui->shapesCmBox->currentData().toInt();
    ElementShapesColors_[shapeChanged] = ui->colorPickingButton->getColor();
    update();
}

void ShapesColorsDialog::on_shapesCmBox_currentIndexChanged(int index)
{
    ui->colorPickingButton->setColor(ElementShapesColors_[index]);
    update();
}

void ShapesColorsDialog::on_buttonBox_accepted()
{
    accept();
}

void ShapesColorsDialog::on_buttonBox_rejected()
{
    reject();
}
