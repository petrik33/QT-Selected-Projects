#include "calculator.h"
#include "ui_calculator.h"
#include "QValidator"
#include "QMessageBox"

int n1 = 0, n2 = 0;
QValidator* val = new QIntValidator(-1000000,1000000);

Calculator::Calculator(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Calculator)
{
    ui->setupUi(this);
//    ui->edN1->setValidator(val);
//    ui->edN2->setValidator(val);
}

Calculator::~Calculator()
{
    delete val;
    delete ui;
}

void Calculator::validate(QWidget* sender, int &n)
{
//    if(QLineEdit * le = dynamic_cast<QLineEdit*>(sender))
    if(typeid (*sender) == typeid (QLineEdit))
    {
        QLineEdit* le = (QLineEdit*)sender;
        QString s = le->text();
        int k = n;
        if(val->validate(s,k) != QValidator::Acceptable)
        {
            QMessageBox::information(this,"Ошибка","Введите целое число!");
            le->setFocus();
            n = 0;
            le->setText(QString::number(n));
        }
        else
        {
            n = k;
        }
    }
}

void Calculator::checkN2()
{
    if(n2 == 0)
    {
        ui->btDiv->setEnabled(false);
    }
    else
    {
        ui->btDiv->setEnabled(true);
    }
}

void Calculator::on_btSub_clicked()
{
    ui->edRezt->setText(QString::number(n1-n2));
}

void Calculator::on_edN1_editingFinished()
{
    n1=(ui->edN1->text()).toInt();
    validate(ui->edN1,n1);
}

void Calculator::on_edN2_editingFinished()
{
    n2=(ui->edN2->text()).toInt();
    validate(ui->edN2,n2);
    checkN2();
}

void Calculator::on_btSum_clicked()
{
    ui->edRezt->setText(QString::number(n1+n2));
}

void Calculator::on_btDiv_clicked()
{
    ui->edRezt->setText(QString::number(n1/n2));
}

void Calculator::on_btMul_clicked()
{
    ui->edRezt->setText(QString::number(n1*n2));
}
