#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QList>
#include <QLabel>
#include <QLineEdit>
#include <QFile>
#include "systemnumber.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:
//    void convert_numbers(const SystemNumber& num);

private slots:
    void on_ledit_decimal_editingFinished();

    void on_ledit_binary_editingFinished();

    void on_ledit_8base_editingFinished();

    void on_ledit_hexagonal_editingFinished();

    void on_ledit_freeBase_editingFinished();

    void on_pushButtonUpdate_pressed();

    void on_pushButtonUpdate_clicked();

    void on_CBoxFreeBase_currentIndexChanged(int index);

    void on_actionReset_triggered();

    void on_pushButtonPath_clicked();

    void on_checkBoxReadFile_stateChanged(int arg1);

    void on_actionExit_triggered();

private:
    QStringList checkBoxOptions = {"24","32","40"};
    QList <QLineEdit> ledits;
    QFile fileRead;
    bool readFromFile = false;
    int freeSysBase = -1;
    SystemNumber* lastEdited = nullptr;
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
