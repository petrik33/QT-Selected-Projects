#ifndef PASSENGERDIALOG_H
#define PASSENGERDIALOG_H

#include <QDialog>
#include <flightdata.h>
#include <QMessageBox>

namespace Ui {
class PassengerDialog;
}

class PassengerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PassengerDialog(QWidget *parent = nullptr);
    Person *personFromDialog();
    ~PassengerDialog();

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::PassengerDialog *ui;
    bool validateInput(bool messageBoxes = false);
};

#endif // PASSENGERDIALOG_H
