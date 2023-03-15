#ifndef SHAPESCOLORSDIALOG_H
#define SHAPESCOLORSDIALOG_H

#include <QDialog>
#include <QPainter>
#include <QtMath>

enum ElementShape{ Rectangly, Circle, Triangle, Hexagon, Dash, Letter_T, Square, ElementShapeEnumSize };

namespace Ui {
class ShapesColorsDialog;
}

class ShapesColorsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ShapesColorsDialog(QWidget *parent = nullptr);
    void setItemSize(int _itemSize = 75);
    QColor ElementShapesColors_[ElementShapeEnumSize] = {Qt::black};
    ~ShapesColorsDialog();

protected:
    void paintEvent(QPaintEvent* event) override;

private slots:
    void on_colorPickingButton_clicked();

    void on_shapesCmBox_currentIndexChanged(int index);

    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::ShapesColorsDialog *ui;
    int itemX,itemY,itemSize;
};

#endif // SHAPESCOLORSDIALOG_H
