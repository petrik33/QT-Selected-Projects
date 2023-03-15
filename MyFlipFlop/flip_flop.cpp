#include "mainwindow.h"
#include "FlipFlop.h"
#include "ui_mainwindow.h"
#include <QPicture>
#include <QMessageBox>

FlipFlop ff;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    for (auto i = 0; i < 4; i++) {
        ui -> twFlipFlop -> setColumnWidth(i, 70);
        ui -> twFlipFlop -> setRowHeight(i, 70);
    }
//    itFlip -> setText("Flip");
//    itFlop -> setText("Flop");
//    itFlip -> setBackground(QBrush(Qt::red));
//    itFlop -> setBackground(QBrush(Qt::green));
    QPixmap pixFlip = QPixmap("/home/OVERLORD/Pictures/elon.jpg").scaled(70, 70, Qt::IgnoreAspectRatio);
    QPixmap pixFlop = QPixmap("/home/OVERLORD/Pictures/oskar-uaild1.jpg").scaled(70, 70, Qt::IgnoreAspectRatio);
    itFlip -> setData(Qt::DecorationRole, pixFlip);
    itFlop -> setData(Qt::DecorationRole, pixFlop);
    showTable();
}

void MainWindow::showTable()
{
    for (auto i = 0; i < 4; i++)
        for (auto j = 0; j < 4; j++)
            if (ff.getItem(i, j))
                ui->twFlipFlop->setItem(i, j, new QTableWidgetItem(*itFlip));
            else
                ui->twFlipFlop->setItem(i, j, new QTableWidgetItem(*itFlop));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_twFlipFlop_cellDoubleClicked(int row, int column)
{
    ff.reCalc(row,column);
    showTable();
    if (ff.isFinished())
    {
//        QMessageBox::information(this, "Игра закончена!", "Победа!");
//        QApplication::quit();
        if (QMessageBox::question(this, "Игра закончена!", "Победа! Желаете сыграть снова?", QMessageBox::Yes | QMessageBox::No) == QMessageBox::No)
            QApplication::quit();
        else {
            ff.startGame();
            showTable();
        }
    }
}

void MainWindow::on_menuNewGame_triggered()
{
    ff.startGame();
    showTable();
}

void MainWindow::on_menuRestart_triggered()
{
    ff.restartGame();
    showTable();
}

void MainWindow::on_menuExit_triggered()
{
    QApplication::quit();
}
