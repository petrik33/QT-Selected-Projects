#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QMenu>
#include <QColorDialog>
#include <QFontDialog>
#include <QCheckBox>
#include <QInputDialog>
#include <QVBoxLayout>
#include <QPushButton>
#include <QImage>
#include <QFileDialog>
#include <QMessageBox>
#include <QSpinBox>
#include <QRadioButton>
#include <QButtonGroup>
#include <QContextMenuEvent>
#include <QLabel>
#include <clock.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected slots:
    void onShapeButtonsClicked(int id);
    void onBackgroundAsImageClicked(int id);
    void onDigitsTypeButtonsClicked(int id);
    void onClockSizeClicked(int id);
    void onShowArrowsClicked(int id);
    void onSecondsShowChecked(int id);
    void onFileChoose();
    void onPenColorClicked();
    void onPenWidthClicked();
    void onBrushColorClicked();
    void onFontClicked();
    void onAppExit();

private:
    Clock* clock;
};
#endif // MAINWINDOW_H
