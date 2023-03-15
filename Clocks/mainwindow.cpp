#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    resize(800,800);
    setMinimumSize(800,800);
    setWindowTitle("ClockWork");

    QMenu* fileMenu = new QMenu("File");

    QAction* fileChoose = new QAction("Choose...");
    connect(fileChoose,SIGNAL(triggered()),this,SLOT(onFileChoose()));
    QAction* actExit = new QAction("Exit");
    connect(actExit,SIGNAL(triggered()),this,SLOT(onAppExit()));

    fileMenu->addAction(fileChoose);
    fileMenu->addSeparator();
    fileMenu->addAction(actExit);

    QMenu* settingsMenu = new QMenu("Settings");

    QAction* actFontChoose = new QAction("Font...");
    connect(actFontChoose,SIGNAL(triggered()),this,SLOT(onFontClicked()));
    QAction* actPenWidth = new QAction("Pen Width...");
    connect(actPenWidth,SIGNAL(triggered()),this,SLOT(onPenWidthClicked()));
    QAction* actPenColor = new QAction("Pen Color...");
    connect(actPenColor,SIGNAL(triggered()),this,SLOT(onPenColorClicked()));
    QAction* actBrushColor = new QAction("Brush Color...");
    connect(actBrushColor,SIGNAL(triggered()),this,SLOT(onBrushColorClicked()));

    settingsMenu->addAction(actFontChoose);
    settingsMenu->addAction(actPenWidth);
    settingsMenu->addAction(actPenColor);
    settingsMenu->addAction(actBrushColor);

    menuBar()->addMenu(fileMenu);
    menuBar()->addMenu(settingsMenu);

    QWidget* w = new QWidget(this);
    setCentralWidget(w);

    QHBoxLayout* mainLayout = new QHBoxLayout();

    QVBoxLayout* clockLayout = new QVBoxLayout();

    QButtonGroup* sizeSelection = new QButtonGroup();

    QRadioButton* sizeSmall = new QRadioButton("Small");
    QRadioButton* sizeMedium = new QRadioButton("Medium");
    QRadioButton* sizeBig = new QRadioButton("Big");
    sizeSelection->addButton(sizeSmall,0);
    sizeSelection->addButton(sizeMedium,1);
    sizeSelection->addButton(sizeBig,2);

    sizeMedium->setChecked(true);

    connect(sizeSelection,SIGNAL(buttonClicked(int)),this,SLOT(onClockSizeClicked(int)));

    QHBoxLayout* szlayout = new QHBoxLayout();
    szlayout->addWidget(sizeSmall);
    szlayout->addWidget(sizeMedium);
    szlayout->addWidget(sizeBig);

    clock = new Clock(this);
    clock->setMinimumSize(600,600);

    clockLayout->addWidget(clock);
    clockLayout->addLayout(szlayout);

    QVBoxLayout* buttonsVLayout = new QVBoxLayout();

    QButtonGroup* digitsSelection = new QButtonGroup();

    QRadioButton* digitsArabic = new QRadioButton("Arabic");
    QRadioButton* digitsRoman = new QRadioButton("Roman");

    digitsSelection->addButton(digitsArabic,Arabic);
    digitsSelection->addButton(digitsRoman,Roman);
    digitsRoman->setChecked(true);

    connect(digitsSelection,SIGNAL(buttonClicked(int)),this,SLOT(onDigitsTypeButtonsClicked(int)));

    QHBoxLayout* dlayout = new QHBoxLayout();
    dlayout->addWidget(digitsArabic);
    dlayout->addWidget(digitsRoman);

    buttonsVLayout->addLayout(dlayout);

    QCheckBox* chkBoxShowSeconds = new QCheckBox("Seconds");
    connect(chkBoxShowSeconds,SIGNAL(stateChanged(int)),this,SLOT(onSecondsShowChecked(int)));

    buttonsVLayout->addWidget(chkBoxShowSeconds);
    chkBoxShowSeconds->setCheckState(Qt::Checked);

    QCheckBox* chkBoxShowArrows = new QCheckBox("Arrows");
    connect(chkBoxShowArrows,SIGNAL(stateChanged(int)),this,SLOT(onShowArrowsClicked(int)));

    buttonsVLayout->addWidget(chkBoxShowArrows);
    chkBoxShowArrows->setCheckState(Qt::Checked);

    QCheckBox* chkBackgroundAsImage = new QCheckBox("Image BG");
    connect(chkBackgroundAsImage,SIGNAL(stateChanged(int)),this,SLOT(onBackgroundAsImageClicked(int)));
    chkBackgroundAsImage->setCheckState(Qt::Unchecked);

    buttonsVLayout->addWidget(chkBackgroundAsImage);

    QButtonGroup* shapeSelection = new QButtonGroup();

    QRadioButton* shapeSquare = new QRadioButton("Square");
    QRadioButton* shapeRound = new QRadioButton("Round");
    shapeSelection->addButton(shapeSquare,Square);
    shapeSelection->addButton(shapeRound,Round);
    shapeRound->setChecked(true);

    connect(shapeSelection,SIGNAL(buttonClicked(int)),this,SLOT(onShapeButtonsClicked(int)));

    QHBoxLayout* slayout = new QHBoxLayout();
    slayout->addWidget(shapeSquare);
    slayout->addWidget(shapeRound);

    buttonsVLayout->addLayout(slayout);

    centralWidget()->setLayout(mainLayout);

    mainLayout->addLayout(clockLayout);
    mainLayout->addLayout(buttonsVLayout);

}

MainWindow::~MainWindow()
{

}

void MainWindow::onShapeButtonsClicked(int id)
{
    clock->setShapeType(ClockShape(id));
}

void MainWindow::onBackgroundAsImageClicked(int id)
{
    if(id == Qt::Unchecked)
    {
        clock->enableBGImage(false);
    }
    else
    {
        clock->enableBGImage(true);
    }
}

void MainWindow::onDigitsTypeButtonsClicked(int id)
{
    clock->setDigitsType(DigitsType(id));
}

void MainWindow::onClockSizeClicked(int id)
{
    switch (id) {
    case 2:
        clock->setClockSizePart(0.9);
        break;
    case 1:
        clock->setClockSizePart(0.7);
        break;
    case 0:
        clock->setClockSizePart(0.5);
        break;
    }


}

void MainWindow::onShowArrowsClicked(int id)
{
    if(id == Qt::Unchecked)
    {
        clock->setClockArrowsEnabled(false);
    }
    else
    {
        clock->setClockArrowsEnabled(true);
    }
}

void MainWindow::onSecondsShowChecked(int id)
{
    if(id == Qt::Unchecked)
    {
        clock->enableSecond(false);
    }
    else
    {
        clock->enableSecond(true);
    }
}

void MainWindow::onFileChoose()
{
    QString fileName = QFileDialog::getOpenFileName(this,"Image","","Images (*.png *.xpm *.jpg)");
    if(fileName.isEmpty()) return;
    clock->setBGImageFromFile(fileName);
}

void MainWindow::onPenColorClicked()
{
    QColor color = QColorDialog::getColor(Qt::white,this,"Pen Color");
    if(!color.isValid()) return;
    clock->setPenColor(color);
}

void MainWindow::onPenWidthClicked()
{
    bool ok;
    int width = QInputDialog::getInt(this,"Pen Width","pen width",1,1,50,1,&ok);
    if(!ok) return;
    clock->setPenWidth(width);
}

void MainWindow::onBrushColorClicked()
{
    QColor color = QColorDialog::getColor(Qt::white,this,"Brush Color");
    if(!color.isValid()) return;
    clock->setBrushColor(color);
}

void MainWindow::onFontClicked()
{
    bool ok;
    QFont font = QFontDialog::getFont(&ok,this);
    if(!ok) return;
    clock->setFont(font);
}

void MainWindow::onAppExit()
{
    QApplication::quit();
}

