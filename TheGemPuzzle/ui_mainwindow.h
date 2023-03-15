/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>
#include "digitalclock.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionStart;
    QAction *actionRestart;
    QAction *actionExit;
    QWidget *centralwidget;
    QTableWidget *GemPuzzleTable;
    QLineEdit *MovesOutput;
    DigitalClock *GameClock;
    QMenuBar *menubar;
    QMenu *menu;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1000, 600);
        actionStart = new QAction(MainWindow);
        actionStart->setObjectName(QString::fromUtf8("actionStart"));
        actionRestart = new QAction(MainWindow);
        actionRestart->setObjectName(QString::fromUtf8("actionRestart"));
        actionExit = new QAction(MainWindow);
        actionExit->setObjectName(QString::fromUtf8("actionExit"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        GemPuzzleTable = new QTableWidget(centralwidget);
        if (GemPuzzleTable->columnCount() < 4)
            GemPuzzleTable->setColumnCount(4);
        if (GemPuzzleTable->rowCount() < 4)
            GemPuzzleTable->setRowCount(4);
        GemPuzzleTable->setObjectName(QString::fromUtf8("GemPuzzleTable"));
        GemPuzzleTable->setGeometry(QRect(300, 100, 400, 400));
        QFont font;
        font.setFamily(QString::fromUtf8("Courier"));
        font.setPointSize(20);
        font.setBold(true);
        font.setWeight(75);
        GemPuzzleTable->setFont(font);
        GemPuzzleTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
        GemPuzzleTable->setProperty("showDropIndicator", QVariant(true));
        GemPuzzleTable->setDragEnabled(false);
        GemPuzzleTable->setSelectionMode(QAbstractItemView::NoSelection);
        GemPuzzleTable->setVerticalScrollMode(QAbstractItemView::ScrollPerItem);
        GemPuzzleTable->setShowGrid(true);
        GemPuzzleTable->setGridStyle(Qt::SolidLine);
        GemPuzzleTable->setCornerButtonEnabled(true);
        GemPuzzleTable->setRowCount(4);
        GemPuzzleTable->setColumnCount(4);
        GemPuzzleTable->horizontalHeader()->setVisible(false);
        GemPuzzleTable->verticalHeader()->setVisible(false);
        MovesOutput = new QLineEdit(centralwidget);
        MovesOutput->setObjectName(QString::fromUtf8("MovesOutput"));
        MovesOutput->setEnabled(true);
        MovesOutput->setGeometry(QRect(300, 0, 400, 60));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Courier"));
        font1.setPointSize(14);
        MovesOutput->setFont(font1);
        MovesOutput->setAlignment(Qt::AlignCenter);
        MovesOutput->setReadOnly(true);
        GameClock = new DigitalClock(centralwidget);
        GameClock->setObjectName(QString::fromUtf8("GameClock"));
        GameClock->setGeometry(QRect(760, 0, 240, 60));
        GameClock->setSmallDecimalPoint(false);
        GameClock->setDigitCount(6);
        GameClock->setMode(QLCDNumber::Dec);
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1000, 31));
        menu = new QMenu(menubar);
        menu->setObjectName(QString::fromUtf8("menu"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menu->menuAction());
        menu->addAction(actionStart);
        menu->addAction(actionRestart);
        menu->addAction(actionExit);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "The Gem Puzzle", nullptr));
        actionStart->setText(QCoreApplication::translate("MainWindow", "Start", nullptr));
        actionRestart->setText(QCoreApplication::translate("MainWindow", "Restart", nullptr));
        actionExit->setText(QCoreApplication::translate("MainWindow", "Exit", nullptr));
        MovesOutput->setText(QCoreApplication::translate("MainWindow", " Moves Made: ", nullptr));
        menu->setTitle(QCoreApplication::translate("MainWindow", "Game", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
