#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{

    resize(400,600);
    setWindowTitle("Trigonometry");

    QWidget* cWidget = new QWidget(this);
    setCentralWidget(cWidget);

    //File Menu
    QMenu* fileMenu = new QMenu("File");

    QAction* fileSave = new QAction("Save Log...");
    connect(fileSave,SIGNAL(triggered(bool)),this,SLOT(onSaveLog()));

    QAction* fileRead = new QAction("Read...");
    connect(fileRead,SIGNAL(triggered(bool)),this,SLOT(onRead()));

    fileMenu->addAction(fileSave);
    fileMenu->addAction(fileRead);
    fileMenu->addSeparator();

    QAction* appExit = new QAction("Exit");
    connect(appExit,SIGNAL(triggered(bool)),this,SLOT(close()));

    fileMenu->addAction(appExit);
    menuBar()->addMenu(fileMenu);

    QVBoxLayout* mainLayout = new QVBoxLayout(centralWidget());

    QHBoxLayout* inputLayout = new QHBoxLayout();

    cmbBxFunctions = new QComboBox();
    QStringList functions = {"Asin","Acos","Atan","Acatan"};
    cmbBxFunctions->addItems(functions);
    cmbBxFunctions->setCurrentIndex(ASIN);
    connect(cmbBxFunctions,SIGNAL(currentIndexChanged(int)),this,SLOT(onFunctionChanged(int)));

    lnEdtInput = new QLineEdit();
    inputLayout->addWidget(cmbBxFunctions);
    inputLayout->addWidget(lnEdtInput);

    mainLayout->addLayout(inputLayout);

    lnEdtResult = new QLineEdit();
    lnEdtResult->setReadOnly(true);

    mainLayout->addWidget(lnEdtResult);

    btnGrpReadFromFile = new QButtonGroup();
    QRadioButton* rdBtnReadFromFileYes = new QRadioButton("Yes");
    QRadioButton* rdBtnReadFromFileNo = new QRadioButton("No");
    rdBtnReadFromFileNo->setChecked(true);
    btnGrpReadFromFile->addButton(rdBtnReadFromFileNo,false);
    btnGrpReadFromFile->addButton(rdBtnReadFromFileYes,true);
    connect(btnGrpReadFromFile,SIGNAL(buttonClicked(int)),this,SLOT(onReadButtonGroupClicked(int)));

    QHBoxLayout* readLayout = new QHBoxLayout();

    QLabel* lblReadFromFile = new QLabel("Read From File");

    readLayout->addWidget(lblReadFromFile);
    readLayout->addWidget(rdBtnReadFromFileYes);
    readLayout->addWidget(rdBtnReadFromFileNo);

    mainLayout->addLayout(readLayout);

    pshBtnCount = new QPushButton("Count");
    connect(pshBtnCount,SIGNAL(clicked()),this,SLOT(onCountClicked()));
    mainLayout->addWidget(pshBtnCount);

    lstVwCountHistory = new QListWidget();
    lstVwCountHistory->setEditTriggers(QAbstractItemView::NoEditTriggers);
    mainLayout->addWidget(lstVwCountHistory);

}

MainWindow::~MainWindow()
{
//    delete ui;
}

void MainWindow::onSaveLog()
{
    QString fileName = QFileDialog::getSaveFileName(this,"Save");
    if(!fileName.isEmpty())
    {
        QFile saveFile(fileName);
        saveFile.open(QIODevice::WriteOnly);
        QTextStream s(&saveFile);
        for(int i = 0; i < history.size(); i++)
        {
            s << history[i] << "\n";
        }
    }
}

void MainWindow::onRead()
{
    filePath = QFileDialog::getOpenFileName(this,"Read","","Text (*.txt)");
    if(readFile) lnEdtInput->setText(readNumberFromFile());
}

void MainWindow::onCountClicked()
{
    QString input;
    if(!readFile)
    {
       input = lnEdtInput->text();
    }
    else
    {
        QFile fileRead(filePath);
        if(!fileRead.open(QIODevice::ReadOnly)){
            QMessageBox::critical(this,"Error","Can't open file or file isn't chosen.");
            return;
        }
        QByteArray block;
        block = fileRead.readLine();
        input = QString(block);
    }
    bool ok;
    double number = input.toDouble(&ok);
    if(!ok)
    {
        QMessageBox::warning(this,"Error","Wrong input.");
        return;
    }
    QString output = countFunction(number);
    lnEdtResult->setText(output);
    history.push_front(output);
    lstVwCountHistory->insertItem(0,output);
}

void MainWindow::onReadButtonGroupClicked(int id)
{
    readFile = id;
    if(readFile)
    {
        lnEdtInput->setText(readNumberFromFile());
        lnEdtInput->setReadOnly(true);
    }
    else
    {
        lnEdtInput->setReadOnly(false);
    }
}

void MainWindow::onFunctionChanged(int id)
{
    funcChosen = TFunctions(id);
}

QString MainWindow::countFunction(double value)
{
    double resultAngle;
    switch (funcChosen) {
    case ASIN:
        resultAngle = asin(value);
        break;
    case ACOS:
        resultAngle = acos(value);
        break;
    case ATAN:
        resultAngle = atan(value);
        break;
    case ACATAN:
        resultAngle = atan(1/value);
        break;
    }
    QString output = QString::number(resultAngle) + " Radians or ";
    output += QString::number(qRadiansToDegrees(resultAngle)) + " degrees";
    return output;
}

QString MainWindow::readNumberFromFile()
{
    QString input;
    QFile fileRead(filePath);
    if(!fileRead.open(QIODevice::ReadOnly)){
        return "";
    }
    QByteArray block;
    block = fileRead.readLine();
    input = QString(block);
    return input;
}

