#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "digitalclock.h"
#include "gempuzzle.h"
#include <QMessageBox>
#include <QLineEdit>

GemPuzzle gameModel;
QFont tableFont("Courier", 100);

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->GemPuzzleTable->setColumnCount(4);
    ui->GemPuzzleTable->setRowCount(4);

    int windowCenterX = width() / 2;
    int windowCenterY = height() / 2;

    int tableSide = 402;

    ui->GemPuzzleTable->setGeometry(windowCenterX - tableSide / 2,windowCenterY - tableSide/2,tableSide,tableSide);
    tableFont.setBold(true);
    ui->GemPuzzleTable->setFont(tableFont);
    for (auto i=0; i< 4; i++)
    {
        ui->GemPuzzleTable->setColumnWidth(i,100);
        ui->GemPuzzleTable->setRowHeight(i,100);
    }

    ui->GameClock->RestartTime();

    puzzleCell->setTextAlignment(Qt::AlignCenter);
    QPixmap pixEmptyCell = QPixmap("EmptyCell2.png");
    puzzleEmptyCell->setData(Qt::DecorationRole,pixEmptyCell);

    showGameTable();
}

void MainWindow::showGameTable(){
    for(auto x = 0; x < 4; x++)
    {
        for(auto y = 0; y < 4; y++)
        {
            QTableWidgetItem* cellItem = new QTableWidgetItem(*puzzleCell);
            cellItem->setText(QString::number(gameModel.getCell(x,y)));
            ui->GemPuzzleTable->setItem(x,y,cellItem);
        }
    }
    ui->GemPuzzleTable->setItem(gameModel.getEmptyX(),gameModel.getEmptyY(),new QTableWidgetItem(*puzzleEmptyCell));
    ui->MovesOutput->setText("Moves Made: " + QString::number(gameModel.getMovesNumber()));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_GemPuzzleTable_cellClicked(int row, int column)
{
    if(gameModel.moveCellInGame(row,column))
    {
        showGameTable();
    }
    if(gameModel.isFinished())
    {
        ui->GameClock->StopTime();
        if (QMessageBox::question(this, "Игра закончена!", "Победа! Желаете сыграть еще?" ,
                              QMessageBox::Yes | QMessageBox:: No)==QMessageBox::No)
        {
            //Nothing
        }
        else
        {
            gameModel.startGame();
            ui->GameClock->RestartTime();
            showGameTable();
        }
    }
}

void MainWindow::on_actionStart_triggered()
{
    gameModel.startGame();
    ui->GameClock->RestartTime();
    showGameTable();
}

void MainWindow::on_actionRestart_triggered()
{
    gameModel.restartGame();
    ui->GameClock->RestartTime();
    showGameTable();
}

void MainWindow::on_actionExit_triggered()
{
    QApplication::exit();
}
