#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidgetItem>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_GemPuzzleTable_cellClicked(int row, int column);

    void on_actionStart_triggered();

    void on_actionRestart_triggered();

    void on_actionExit_triggered();

private:
    Ui::MainWindow *ui;
    QTableWidgetItem *puzzleCell=new QTableWidgetItem ;
    QTableWidgetItem *puzzleEmptyCell=new QTableWidgetItem ;
    void showGameTable();
};
#endif // MAINWINDOW_H
