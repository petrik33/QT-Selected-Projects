#ifndef GRAPHICSSETTINGSDIALOG_H
#define GRAPHICSSETTINGSDIALOG_H

#include <QDialog>
#include "elementsettings.h"
#include <QLabel>
#include <QComboBox>
#include <QSpinBox>

const int IdRole = Qt::UserRole;

namespace Ui {
class graphicsSettingsDialog;
}

class graphicsSettingsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit graphicsSettingsDialog(QWidget *parent = nullptr);
    ~graphicsSettingsDialog();
    Qt::PenJoinStyle getPenJoinStyle() const;
    Qt::PenCapStyle getPenCapStyle() const;
    Qt::PenStyle getPenStyle() const;
    int getPenWidth() const;
    Qt::BrushStyle getBrushStyle() const;
private slots:
//    void ElementShapeChanged();
//    void penChanged();
//    void brushChanged();

    void on_graphicsSettingsBBox_accepted();

    void on_graphicsSettingsBBox_rejected();

private:
//    ElementSettings *elementSettings;
//    QLabel *ElementShapeLabel;
//    QLabel *penWidthLabel;
//    QLabel *penStyleLabel;
//    QLabel *penCapLabel;
//    QLabel *penJoinLabel;
//    QLabel *brushStyleLabel;
//    QLabel *otherOptionsLabel;
//    QComboBox *ElementShapeComboBox;
//    QSpinBox *penWidthSpinBox;
//    QComboBox *ui->cmboxPenStyle;
//    QComboBox *penCapComboBox;
//    QComboBox *penJoinComboBox;
//    QComboBox *ui->cmboxBrushStyle;

    Ui::graphicsSettingsDialog *ui;
};

#endif // GRAPHICSSETTINGSDIALOG_H
