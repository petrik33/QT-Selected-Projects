#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QErrorMessage"
#include "QMessageBox"
#include "QFileDialog"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->CBoxFreeBase->addItems(checkBoxOptions);
//    QObject::connect(this,SIGNAL(convert_numbers()),this,SLOT(on_ledit_decimal_editingFinished()));
//    QObject::connect(this,SIGNAL(convert_numbers()),this,SLOT(on_ledit_binary_editingFinished()));
//    QObject::connect(this,SIGNAL(convert_numbers()),this,SLOT(on_ledit_free_editingFinished()));
//    QObject::connect(this,SIGNAL(convert_numbers()),this,SLOT(on_ledit_8base_editingFinished()));
//    QObject::connect(this,SIGNAL(convert_numbers()),this,SLOT(on_ledit_hexagonal_editingFinished()));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_ledit_decimal_editingFinished()
{
    QString input = ui->ledit_decimal->text();
    if(SystemNumber::numberValidate(input,10))
    {
        if(lastEdited != nullptr) delete lastEdited;
        lastEdited = new SystemNumber(input,10);
    }
    else
    {
        QMessageBox::warning(this,"Wrong input","Please, enter valid data for that numeric base or choose different one.");
    }
}

void MainWindow::on_ledit_binary_editingFinished()
{
    QString input = ui->ledit_binary->text();
    if(SystemNumber::numberValidate(input,2))
    {
        if(lastEdited != nullptr) delete lastEdited;
        lastEdited = new SystemNumber(input,2);
    }
    else
    {
        QMessageBox::warning(this,"Wrong input","Please, enter valid data for that numeric base or choose different one.");
    }
}

void MainWindow::on_ledit_8base_editingFinished()
{
    QString input = ui->ledit_8base->text();
    if(SystemNumber::numberValidate(input,8))
    {
        if(lastEdited != nullptr) delete lastEdited;
        lastEdited = new SystemNumber(input,8);
    }
    else
    {
        QMessageBox::warning(this,"Wrong input","Please, enter valid data for that numeric base or choose different one.");
    }
}

void MainWindow::on_ledit_hexagonal_editingFinished()
{
    QString input = ui->ledit_hexagonal->text();
    if(SystemNumber::numberValidate(input,16))
    {
        if(lastEdited != nullptr) delete lastEdited;
        lastEdited = new SystemNumber(input,16);
    }
    else
    {
        QMessageBox::warning(this,"Wrong input","Please, enter valid data for that numeric base or choose different one.");
    }
}

void MainWindow::on_ledit_freeBase_editingFinished()
{
    QString input = ui->ledit_freeBase->text();
    if(freeSysBase != -1)
    {
        if(SystemNumber::numberValidate(input,freeSysBase))
        {
            if(lastEdited != nullptr) delete lastEdited;
            lastEdited = new SystemNumber(input,freeSysBase);
        }
    }
    else
    {
        QMessageBox::warning(this,"Wrong input","Please, enter valid data for that numeric base or choose different one.");
    }
}

void MainWindow::on_pushButtonUpdate_pressed()
{
    //Wrong Slot
}

void MainWindow::on_pushButtonUpdate_clicked()
{
    if(readFromFile)
    {
        if(lastEdited != nullptr)
        {
            delete lastEdited;
            lastEdited = nullptr;
        }
        if(!fileRead.open(QIODevice::ReadOnly)){
            QErrorMessage err;
            err.showMessage("Failed to open the file. Please, select different file.");
            err.exec();
            return;
        }
        QByteArray block;
        block = fileRead.readLine();
        int base = block.toInt();
        block = fileRead.readLine();
        QString numStr= block;
        if(SystemNumber::numberValidate(numStr,base))
        {
            lastEdited = new SystemNumber(numStr,base);
        }
        else
        {
            QErrorMessage err;
            err.showMessage("File data is formated improperly.Proper format:\nbase\nnumber");
            err.exec();
            return;
        }
    }
    if(lastEdited != nullptr)
    {
        ui->ledit_decimal->setText(SystemNumber::GetNumberInBase(*lastEdited,10));
        ui->ledit_binary->setText(SystemNumber::GetNumberInBase(*lastEdited,2));
        ui->ledit_8base->setText(SystemNumber::GetNumberInBase(*lastEdited,8));
        ui->ledit_hexagonal->setText(SystemNumber::GetNumberInBase(*lastEdited,16));
        if(freeSysBase != -1)
        {
           ui->ledit_freeBase->setText(SystemNumber::GetNumberInBase(*lastEdited,freeSysBase));
        }
        else
        {
            QErrorMessage err;
            err.showMessage("You can choose the base for the last line.");
            err.exec();
        }
    }
}

void MainWindow::on_CBoxFreeBase_currentIndexChanged(int index)
{
    if(index != 0)
    {
        freeSysBase = ui->CBoxFreeBase->currentText().toInt();
    }
}

void MainWindow::on_actionReset_triggered()
{
    ui->ledit_decimal->clear();
    ui->ledit_binary->clear();
    ui->ledit_8base->clear();
    ui->ledit_hexagonal->clear();
    ui->ledit_freeBase->clear();
    freeSysBase = -1;
    ui->CBoxFreeBase->setCurrentIndex(0);
    readFromFile = false;
    ui->checkBoxReadFile->setCheckState(Qt::CheckState::Unchecked);
}

void MainWindow::on_pushButtonPath_clicked()
{
    QString filePath = QFileDialog::getOpenFileName(
                this,
                tr("Open Text File"),
                "/QT/Projects/NumbersConverter",
                tr("Text Files (*.txt)")
                );
    if(!filePath.isEmpty())
    {
        fileRead.setFileName(filePath);
    }
}

void MainWindow::on_checkBoxReadFile_stateChanged(int arg1)
{
    readFromFile = arg1;
}

void MainWindow::on_actionExit_triggered()
{
    QApplication::quit();
}
