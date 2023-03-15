//#include "memotable.h"

//MemoTable::MemoTable(QWidget *parent) : QTableWidget(parent)
//{
//    update();
//    QWidget::setAttribute(Qt::WA_PaintOnScreen);
//}

//MemoTable::MemoTable(int rows, int columns,QWidget * parent) : QTableWidget(rows,columns,parent)
//{
//    update();
//    QWidget::setAttribute(Qt::WA_PaintOnScreen);
//}

//MemoTable::~MemoTable()
//{

//}

////QPaintEngine *MemoTable::paintEngine() const
////{
////    return nullptr;
////}

//void MemoTable::SetGraphics(Qt::PenJoinStyle penJoinStyle, Qt::PenCapStyle penCapStyle, Qt::PenStyle penStyle, int penWidth, Qt::BrushStyle brushStyle)
//{
//    penStyle_ = penStyle;
//    penCapStyle_ = penCapStyle;
//    penWidth_ = penWidth;
//    penJoinStyle_ = penJoinStyle;
//    brushStyle_ = brushStyle;
//}

//void MemoTable::paintEvent(QPaintEvent*  event)
//{
//    QTableWidget::paintEvent(event);
//    QPainter painter(this);

//    QPen pen(Qt::black,penWidth_, penStyle_, penCapStyle_, penJoinStyle_);
////    QBrush brush(Qt::black,brushStyle_);
//    painter.setPen(pen);

//    int itemMaxHeight = rowHeight(0);

//    for(int i = 0; i < rowCount(); i++)
//    {
//        int x = rowViewportPosition(i);
//        for(int j = 0; j < columnCount(); j++)
//        {
//            MemoCell* cell = static_cast<MemoCell*>(item(i,j));
//            ElementShape shape = ElementShape(cell->shape_);
////            brush.setColor(ElementShapesColors_[int(shape)]);
////            painter.setBrush(brush);

//            int y = columnViewportPosition(j);

////            painter->translate(x,y);

//            switch (shape)
//            {
//                case Rectangly:

//                break;

//                case Circle:
//                    painter.drawEllipse(x,y,itemMaxHeight * 0.75,itemMaxHeight * 0.75);
//                    break;

//                default:

//                    break;
//            }
//        }
//    }
//}
