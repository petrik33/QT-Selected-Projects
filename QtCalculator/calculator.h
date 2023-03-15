#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class Calculator; }
QT_END_NAMESPACE

class Calculator : public QDialog
{
    Q_OBJECT

public:
    Calculator(QWidget *parent = nullptr);
    ~Calculator();

private slots:
    void on_btSub_clicked();

    void on_edN1_editingFinished();

    void on_edN2_editingFinished();

    void on_btSum_clicked();

    void on_btDiv_clicked();

    void on_btMul_clicked();

private:
    Ui::Calculator *ui;
    void validate(QWidget* sender,int& n);
    void checkN2();
};
#endif // CALCULATOR_H
