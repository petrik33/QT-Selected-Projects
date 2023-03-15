#ifndef FLIGHTDIALOG_H
#define FLIGHTDIALOG_H

#include <QDialog>
#include <flightdata.h>
#include <QMessageBox>

namespace Ui {
class FlightDialog;
}

class FlightDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FlightDialog(QWidget *parent = nullptr);
    ~FlightDialog();
    FlightData* flightFromDialog();

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::FlightDialog *ui;
    bool validateInput(bool messageBoxes = false);
};

#endif // FLIGHTDIALOG_H
