#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    UpdateGraphics();
    tableX = 4;
    tableY = menuBar()->height() + 4;
    tableWidth = width() - 8;
    tableHeight = height() - tableY - 8;
    tableRows = 2;
    tableColumns = shapesUsed_;
    for(int i = 0; i < tableRows; i++)
    {
        QVector<MemoCell*> row;
        for(int j = 0; j < ElementShapeEnumSize; j++)
        {
           row.push_back(nullptr);
        }
        gameGrid.push_back(row);
    } 
    ui->leditRandomSeed->setText(QString::number(QRandomGenerator::global()->bounded(UINT_MAX % 1000)));
    hideTimer = new QTimer(this);
    connect(hideTimer,SIGNAL(timeout()),this,SLOT(TimerHideCells()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::UpdateGraphics(Qt::PenJoinStyle penJoinStyle, Qt::PenCapStyle penCapStyle, Qt::PenStyle penStyle, int penWidth, Qt::BrushStyle brushStyle)
{
    penStyle_ = penStyle;
    penCapStyle_ = penCapStyle;
    penWidth_ = penWidth;
    penJoinStyle_ = penJoinStyle;
    brushStyle_ = brushStyle;
    update();
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    QMainWindow::paintEvent(event);
    if(drawTable)
    {
        QPainter painter(this);

        int itemWidth = tableWidth / tableColumns;
        int itemHeight = tableHeight / tableRows;

        int itemBoxSize = qMin(itemWidth,itemHeight) * 0.75;
        int itemR = itemBoxSize / 2;

        //Draw Table Frame
        for(int y = 0; y <= tableRows; y++)
        {
            int rowY = tableY + y * itemHeight;
            painter.drawLine(tableX,rowY,tableX+tableWidth,rowY);
        }
        for(int x = 0; x <= tableColumns; x++)
        {
            int columnX = tableX + x * itemWidth;
            painter.drawLine(columnX,tableY,columnX,tableY+tableHeight);
        }

        QPen pen(Qt::black,penWidth_, penStyle_, penCapStyle_, penJoinStyle_);
        QBrush brush(Qt::black,brushStyle_);
        painter.setPen(pen);

        for(int i = 0; i < tableRows; i++)
        {
            int y = tableY + itemHeight * (i) + itemHeight/2;

            for(int j = 0; j < tableColumns; j++)
            {
                MemoCell* cell = gameGrid[i][j];
                if(!cell->visible)
                {
                    continue;
                }
                ElementShape shape = cell->shape;
                brush.setColor(ElementShapesColors_[int(shape)]);
                painter.setBrush(brush);

                int x = tableX + itemWidth * j + itemWidth / 2;

                switch (shape)
                {
                case Square:
                painter.drawRect(
                            x - itemR,
                            y - itemR,
                            itemBoxSize,
                            itemBoxSize
                            );
                    break;

                case Rectangly:
                painter.drawRect(
                            x - itemR,
                            y - itemR/2,
                            itemBoxSize,
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
                                y - itemBoxSize/16,
                                itemBoxSize,
                                itemBoxSize/8,
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
                            itemBoxSize,
                            itemBoxSize
                            );
                    break;

                default:

                    break;
                }
            }
        }
    }
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    QMainWindow::mousePressEvent(event);
    if(drawTable)
    {
        if(event->button() == Qt::LeftButton)
        {
            if(hiding)
            {
                HideCells();
            }
            else
            {
                int mouseX = event->x();
                int mouseY = event->y();
                if(mouseX < tableX || mouseX >= tableX + tableWidth) return;
                if(mouseY < tableY || mouseY >= tableY + tableHeight) return;
                double cellY = double((mouseX - tableX) * tableColumns) / tableWidth;
                double cellX = double((mouseY - tableY) * tableRows) / tableHeight;
                RevealCell(floor(cellX),floor(cellY));
            }
        }
    }
}

void MainWindow::on_actionGraphics_triggered()
{
    graphicsSettingsDialog dlog(this);
    if(dlog.exec() == QDialog::Accepted)
    {
        UpdateGraphics(dlog.getPenJoinStyle(), \
                       dlog.getPenCapStyle(), \
                       dlog.getPenStyle(), \
                       dlog.getPenWidth(), \
                       dlog.getBrushStyle() \
                       );
    }
}

//void MainWindow::on_actionshapesUsed_triggered()
//{
//    bool bOk;
//    int shapesUsedInput = QInputDialog::getInt(this,"Game Settings","Table Size",shapesUsed_,2,8,1,&bOk);
//    if(bOk)
//    {
//        shapesUsed_ = shapesUsedInput;
//    }
//}

void MainWindow::on_pbStartRandom_clicked()
{
    bool ok;
    int randomSeed = ui->leditRandomSeed->text().toInt(&ok);
    if(ok)
    {
        StartGame(randomSeed);
    }
    else
    {
        QMessageBox::warning(this,"Error","Wrong random seed input!");
    }

}

void MainWindow::StartGame(int randomSeed)
{
    delete ui->pbStartRandom;
    delete  ui->leditRandomSeed;
    delete ui->pbStartFile;

    ui->actionShapesColors->setDisabled(true);
    ui->actionShapesUsed->setDisabled(true);
    ui->menuFile->setDisabled(true);

    drawTable = true;

    QRandomGenerator rg;
    rg.seed(randomSeed);
    QList<ElementShape> shapesAvailable;
    int shapesLeft = shapesUsed_ * 2;

    for(int i = 0; i < shapesUsed_; i++)
    {
        shapesAvailable.push_back(static_cast<ElementShape>(i));
        shapesAvailable.push_back(static_cast<ElementShape>(i));
    }

    for(int x = 0; x < 2; x++){
        for(int y = 0; y < shapesUsed_;y++)
        {
            int randomIndex = rg.bounded(shapesLeft);
            ElementShape _shape = shapesAvailable.at(randomIndex);
            MemoCell* cell = new MemoCell(_shape,ElementShapesColors_[int(_shape)]);
            shapesAvailable.removeOne(shapesAvailable.at(randomIndex));
            gameGrid[x][y] = cell;
            shapesLeft--;
        }
    }

    hiding = true;
    hideTimer->start(startHidingTime);

    update();
}

void MainWindow::HideCells()
{
    if(hiding)
    {
        for(int x = 0; x < 2; x++){
            for(int y = 0; y < shapesUsed_;y++)
            {
                MemoCell* cell = gameGrid[x][y];
                if(!cell->guessed)
                {
                    cell->visible = false;
                }
            }
        }
        hiding = false;
    }
    update();
}

void MainWindow::on_actionChoose_triggered()
{
    filePath = QFileDialog::getOpenFileName(this,"Game File","C:\\Qt\\Projects\\MemoGame",".txt");
}

void MainWindow::on_actionExit_triggered()
{
    QApplication::quit();
}

void MainWindow::on_actionShapesUsed_triggered()
{
    bool bOk;
    int shapesUsedInput = QInputDialog::getInt(this,"Game Settings","Table Size",shapesUsed_,2,ElementShapeEnumSize,1,&bOk);
    if(bOk)
    {
        shapesUsed_ = shapesUsedInput;
        tableColumns = shapesUsed_;
    }
}

void MainWindow::on_actionShapesColors_triggered()
{
    ShapesColorsDialog dlog(this);
    if(dlog.exec() == QDialog::Accepted)
    {
        for(int i = 0; i < ElementShapeEnumSize; i++)
        {
            ElementShapesColors_[i] = dlog.ElementShapesColors_[i];
        }
    }
}

void MainWindow::RevealCell(int x, int y)
{
    MemoCell* cell = gameGrid[x][y];
    if(!cell->guessed)
    {
        if(firstRevealed == nullptr)
        {
            cell->visible = true;
            firstRevealed = cell;
        }
        else
        {
            if(!cell->visible){
                cell->visible = true;
                if(firstRevealed->shape == cell->shape)
                {
                    cell->guessed = true;
                    firstRevealed->guessed = true;
                }
                firstRevealed = nullptr;
                hiding = true;
                hideTimer->start(usualHidingTime);
                if(GameFinished())
                {
                    QMessageBox::information(this,"Victory","Congratulations, you've finished the game.");
                }
            }
        }
    }
    update();
}

bool MainWindow::GameFinished() const
{
   if(drawTable)
   {
       for(int x = 0; x < tableRows; x++)
       {
           for(int y = 0; y < tableColumns; y++)
           {
               if(!gameGrid[x][y]->guessed)
               {
                   return false;
               }
           }
       }
   }
   return true;
}

void MainWindow::on_pbStartFile_clicked()
{
    StartGame(33);
}

void MainWindow::TimerHideCells()
{
    hideTimer->stop();
    HideCells();
}
