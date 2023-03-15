#ifndef ADDBOOKDIALOG_H
#define ADDBOOKDIALOG_H

#include <QDialog>
#include <QFormLayout>
#include <QLabel>
#include <QLineEdit>
#include <QDialogButtonBox>

class AddBookDialog : public QDialog
{
    Q_OBJECT
public:
    explicit AddBookDialog(QWidget *parent = nullptr);
    QLineEdit* lnEdtNumber;
    QLineEdit* lnEdtName;
    QLineEdit* lnEdtYear;
    QLineEdit* lnEdtPages;
signals:

};

#endif // ADDBOOKDIALOG_H
