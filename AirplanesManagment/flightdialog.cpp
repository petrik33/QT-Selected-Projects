#include "flightdialog.h"
#include "ui_flightdialog.h"

FlightDialog::FlightDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FlightDialog)
{
    ui->setupUi(this);
}

FlightDialog::~FlightDialog()
{
    delete ui;
}

FlightData *FlightDialog::flightFromDialog()
{
    FlightData* pFlight = nullptr;
    if(validateInput())
    {
        QString number = ui->leditNumber->text();
        QString destination = ui->leditDestination->text();
        QDateTime departure = ui->dtimeEditDeparture->dateTime();
        QDateTime arrival = ui->dtimeEditArrival->dateTime();
        pFlight = new FlightData(number,destination,departure,arrival);
    }
    return pFlight;
}

void FlightDialog::on_buttonBox_accepted()
{
    if(validateInput(true))
    {
        accept();
    }
}

void FlightDialog::on_buttonBox_rejected()
{
    reject();
}

bool FlightDialog::validateInput(bool messageBoxes)
{
    if(ui->leditNumber->text().isEmpty())
    {
        if(messageBoxes)
        {
            QMessageBox::warning(this,"Error","Wrong flight number!");
        }
        return false;
    }
    if(ui->leditDestination->text().isEmpty())
    {
        if(messageBoxes)
        {
            QMessageBox::warning(this,"Error","Wrong flight destination!");
        }
        return false;
    }
    if(ui->dtimeEditArrival->dateTime() < ui->dtimeEditDeparture->dateTime())
    {
        if(messageBoxes)
        {
            QMessageBox::warning(this,"Error","Arrival time can't be earlier than departure!");
        }
        return false;
    }
    return true;
}
