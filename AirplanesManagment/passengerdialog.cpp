#include "passengerdialog.h"
#include "ui_passengerdialog.h"

PassengerDialog::PassengerDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PassengerDialog)
{
    ui->setupUi(this);
}

Person *PassengerDialog::personFromDialog()
{
    Person* pPerson = nullptr;
    if(validateInput())
    {
        QString name = ui->leditName->text();
        QString doc = ui->leditDoc->text();;
        pPerson = new Person(name,doc);
    }
    return pPerson;
}

PassengerDialog::~PassengerDialog()
{
    delete ui;
}

void PassengerDialog::on_buttonBox_accepted()
{
    if(validateInput(true))
    {
        accept();
    }
}

void PassengerDialog::on_buttonBox_rejected()
{
    reject();
}

bool PassengerDialog::validateInput(bool messageBoxes)
{
    if(ui->leditName->text().isEmpty())
    {
        if(messageBoxes)
        {
            QMessageBox::warning(this,"Error","Wrong name!");
        }
        return false;
    }
    if(ui->leditDoc->text().isEmpty())
    {
        if(messageBoxes)
        {
            QMessageBox::warning(this,"Error","Wrong passport id!");
        }
        return false;
    }
    return true;
}
