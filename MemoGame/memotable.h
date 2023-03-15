#ifndef MEMOTABLE_H
#define MEMOTABLE_H

#include <QTableWidget>
#include <QPainter>
#include <QPaintEngine>
#include <memocell.h>

//class MemoTable : public QTableWidget
//{
//    Q_OBJECT
//public:
//    explicit MemoTable(QWidget *parent = nullptr);
//    explicit MemoTable(int rows, int columns,QWidget * parent = nullptr);
//    virtual ~MemoTable();
//    void SetGraphics(Qt::PenJoinStyle penJoinStyle = Qt::MiterJoin, \
//                        Qt::PenCapStyle penCapStyle = Qt::FlatCap, \
//                        Qt::PenStyle penStyle = Qt::SolidLine, \
//                        int penWidth = 2, \
//                        Qt::BrushStyle brushStyle = Qt::LinearGradientPattern);

//signals:

////    MainWindow* mainWindow_ = nullptr;
//protected:
//    void paintEvent(QPaintEvent *event) override;
////    QPaintEngine* paintEngine() const override;
//    Qt::PenJoinStyle penJoinStyle_;
//    Qt::PenCapStyle penCapStyle_;
//    Qt::PenStyle penStyle_;
//    int penWidth_;
//    Qt::BrushStyle brushStyle_;
//    QColor ElementShapesColors_[ElementShapeEnumSize] = {Qt::black}; //Debug
//};

#endif // MEMOTABLE_H
