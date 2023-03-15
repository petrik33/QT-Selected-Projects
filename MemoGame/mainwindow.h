#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QFileDialog>
#include <QTableWidget>
#include <QTableWidgetItem>
#include "graphicssettingsdialog.h"
#include <QInputDialog>
#include <QPainter>
#include <QPen>
#include <QBrush>
#include <QRandomGenerator>
#include <QHeaderView>
#include <QtMath>
#include "shapescolorsdialog.h"
#include <QMouseEvent>
#include <QTimer>

struct MemoCell{
    ElementShape shape;
    QColor color;
    bool guessed;
    bool visible;
    MemoCell(ElementShape _shape,QColor _color, bool _visible = true, bool _guessed = false){
        shape = _shape;
        color = _color;
        visible = _visible;
        guessed = _guessed;
    }
};


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    Qt::PenJoinStyle penJoinStyle_;
    Qt::PenCapStyle penCapStyle_;
    Qt::PenStyle penStyle_;
    int penWidth_;
    Qt::BrushStyle brushStyle_;
    int shapesUsed_ = 4;
    QColor ElementShapesColors_[ElementShapeEnumSize] = {Qt::black};
    void UpdateGraphics(Qt::PenJoinStyle penJoinStyle = Qt::MiterJoin, \
                        Qt::PenCapStyle penCapStyle = Qt::FlatCap, \
                        Qt::PenStyle penStyle = Qt::SolidLine, \
                        int penWidth = 2, \
                        Qt::BrushStyle brushStyle = Qt::SolidPattern);
protected:
    void paintEvent(QPaintEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;

private slots:
    void on_actionGraphics_triggered();

//    void on_actionshapesUsed_triggered();

    void on_pbStartRandom_clicked();

    void on_actionChoose_triggered();

    void on_actionExit_triggered();

    void on_actionShapesUsed_triggered();

    void on_actionShapesColors_triggered();

    void on_pbStartFile_clicked();

    void TimerHideCells();

private:
    Ui::MainWindow *ui;
//    MemoTable* gameTable_;
    QString filePath;
    void StartGame(int randomSeed);
    void RevealCell(int x, int y);
    bool GameFinished() const;
    void HideCells();
    bool drawTable = false;
    bool hiding = false;
    MemoCell* firstRevealed = nullptr;
    QVector <QVector<MemoCell*>> gameGrid;
    int tableX, tableY;
    int tableWidth, tableHeight;
    int tableRows, tableColumns;
    int startHidingTime = 1000 * 5;//MS
    int usualHidingTime = 1000 * 0.5;
    QTimer* hideTimer = nullptr;
};

#endif // MAINWINDOW_H
