#ifndef SYSTEMNUMBER_H
#define SYSTEMNUMBER_H

#include "QString"

const int firstDigitCode = 48;
const int lastDigitCode = 57;
const int digitsNum = lastDigitCode - firstDigitCode + 1;
const int firstLetterCode = 65;

class SystemNumber
{
protected:
    QString numStr;
    unsigned sysBase;
public:
    SystemNumber(QString numStr_, unsigned base = 10);
    SystemNumber(qlonglong num, unsigned base = 10);
    bool setNumber(qlonglong num);
    bool setNumber(const SystemNumber& other);
    bool setNumber(QString numStr_);
    void changeBase(unsigned base);
    static bool numberValidate(QString numStr_, unsigned sysBase);
    static QString GetNumberInBase(const SystemNumber& num, unsigned int base);
    static QChar baseGetChar(int value, int base);
    QString getString() const;
    qlonglong GetDecimal() const;
};

#endif // SYSTEMNUMBER_H
