#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidgetItem>

QT_BEGIN_NAMESPACE
namespace Ui {class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    virtual ~MainWindow();

private slots:
    void on_twFlipFlop_cellDoubleClicked(int row, int column);

    void on_menuNewGame_triggered();

    void on_menuRestart_triggered();

    void on_menuExit_triggered();

private:
    Ui::MainWindow *ui;
    QTableWidgetItem *itFlip = new QTableWidgetItem;
    QTableWidgetItem *itFlop = new QTableWidgetItem;

    void showTable();
};
#endif // MAINWINDOW_H
