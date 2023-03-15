#include "graphicssettingsdialog.h"
#include "ui_graphicssettingsdialog.h"


graphicsSettingsDialog::graphicsSettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::graphicsSettingsDialog)
{
    ui->setupUi(this);
    setWindowTitle("Graphics Settings");

    ui->cmboxPenStyle->addItem(tr("Solid"), static_cast<int>(Qt::SolidLine));
    ui->cmboxPenStyle->addItem(tr("Dash"), static_cast<int>(Qt::DashLine));
    ui->cmboxPenStyle->addItem(tr("Dot"), static_cast<int>(Qt::DotLine));
    ui->cmboxPenStyle->addItem(tr("Dash Dot"), static_cast<int>(Qt::DashDotLine));
    ui->cmboxPenStyle->addItem(tr("Dash Dot Dot"), static_cast<int>(Qt::DashDotDotLine));
    ui->cmboxPenStyle->addItem(tr("None"), static_cast<int>(Qt::NoPen));

    ui->cmboxPenCap->addItem(tr("Flat"), Qt::FlatCap);
    ui->cmboxPenCap->addItem(tr("Square"), Qt::SquareCap);
    ui->cmboxPenCap->addItem(tr("Round"), Qt::RoundCap);

    ui->cmboxPenJoin->addItem(tr("Miter"), Qt::MiterJoin);
    ui->cmboxPenJoin->addItem(tr("Bevel"), Qt::BevelJoin);
    ui->cmboxPenJoin->addItem(tr("Round"), Qt::RoundJoin);

    ui->cmboxBrushStyle->addItem(tr("Linear Gradient"), \
            static_cast<int>(Qt::LinearGradientPattern));
    ui->cmboxBrushStyle->addItem(tr("Radial Gradient"), \
            static_cast<int>(Qt::RadialGradientPattern));
    ui->cmboxBrushStyle->addItem(tr("Conical Gradient"), \
            static_cast<int>(Qt::ConicalGradientPattern));
    ui->cmboxBrushStyle->addItem(tr("Texture"), static_cast<int>(Qt::TexturePattern));
    ui->cmboxBrushStyle->addItem(tr("Solid"), static_cast<int>(Qt::SolidPattern));
    ui->cmboxBrushStyle->addItem(tr("Horizontal"), static_cast<int>(Qt::HorPattern));
    ui->cmboxBrushStyle->addItem(tr("Vertical"), static_cast<int>(Qt::VerPattern));
    ui->cmboxBrushStyle->addItem(tr("Cross"), static_cast<int>(Qt::CrossPattern));
    ui->cmboxBrushStyle->addItem(tr("Backward Diagonal"), static_cast<int>(Qt::BDiagPattern));
    ui->cmboxBrushStyle->addItem(tr("Forward Diagonal"), static_cast<int>(Qt::FDiagPattern));
    ui->cmboxBrushStyle->addItem(tr("Diagonal Cross"), static_cast<int>(Qt::DiagCrossPattern));
    ui->cmboxBrushStyle->addItem(tr("Dense 1"), static_cast<int>(Qt::Dense1Pattern));
    ui->cmboxBrushStyle->addItem(tr("Dense 2"), static_cast<int>(Qt::Dense2Pattern));
    ui->cmboxBrushStyle->addItem(tr("Dense 3"), static_cast<int>(Qt::Dense3Pattern));
    ui->cmboxBrushStyle->addItem(tr("Dense 4"), static_cast<int>(Qt::Dense4Pattern));
    ui->cmboxBrushStyle->addItem(tr("Dense 5"), static_cast<int>(Qt::Dense5Pattern));
    ui->cmboxBrushStyle->addItem(tr("Dense 6"), static_cast<int>(Qt::Dense6Pattern));
    ui->cmboxBrushStyle->addItem(tr("Dense 7"), static_cast<int>(Qt::Dense7Pattern));
    ui->cmboxBrushStyle->addItem(tr("None"), static_cast<int>(Qt::NoBrush));

}

graphicsSettingsDialog::~graphicsSettingsDialog()
{
    delete ui;
}

Qt::PenJoinStyle graphicsSettingsDialog::getPenJoinStyle() const
{
    return Qt::PenJoinStyle((ui->cmboxPenJoin->currentData(IdRole)).toInt());
}

Qt::PenCapStyle graphicsSettingsDialog::getPenCapStyle() const
{
    return Qt::PenCapStyle((ui->cmboxPenCap->currentData(IdRole)).toInt());
}

Qt::PenStyle graphicsSettingsDialog::getPenStyle() const
{
    return Qt::PenStyle((ui->cmboxPenStyle->currentData(IdRole)).toInt());
}

int graphicsSettingsDialog::getPenWidth() const
{
    return ui->spinboxPenWidth->value();
}

Qt::BrushStyle graphicsSettingsDialog::getBrushStyle() const
{
    return Qt::BrushStyle((ui->cmboxBrushStyle->currentData(IdRole)).toInt());
}

void graphicsSettingsDialog::on_graphicsSettingsBBox_accepted()
{
    accept();
}

void graphicsSettingsDialog::on_graphicsSettingsBBox_rejected()
{
    reject();
}
