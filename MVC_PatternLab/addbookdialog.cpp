#include "addbookdialog.h"

AddBookDialog::AddBookDialog(QWidget *parent) : QDialog(parent)
{
    QFormLayout* mainLayout = new QFormLayout();

    QLabel* lblNumber = new QLabel("Number");
    lnEdtNumber = new QLineEdit();
    lblNumber->setBuddy(lnEdtNumber);

    mainLayout->addRow(lblNumber,lnEdtNumber);

    QLabel* lblName = new QLabel("Name");
    lnEdtName = new QLineEdit();
    lblName->setBuddy(lnEdtName);

    mainLayout->addRow(lblName,lnEdtName);

    QLabel* lblYear = new QLabel("Year");
    lnEdtYear = new QLineEdit();
    lblYear->setBuddy(lnEdtYear);

    mainLayout->addRow(lblYear,lnEdtYear);

    QLabel* lblPages = new QLabel("Pages");
    lnEdtPages = new QLineEdit();
    lblPages->setBuddy(lnEdtPages);

    mainLayout->addRow(lblPages,lnEdtPages);

    QDialogButtonBox* box = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    connect(box,SIGNAL(accepted()),this,SLOT(accept()));
    connect(box,SIGNAL(rejected()),this,SLOT(reject()));

    mainLayout->addWidget(box);

    setLayout(mainLayout);
    setWindowTitle("Add Book");
}
