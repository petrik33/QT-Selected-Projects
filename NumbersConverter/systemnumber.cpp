#include "systemnumber.h"
#include "QErrorMessage"

bool SystemNumber::numberValidate(QString numStr_, unsigned sysBase)
{
    if(numStr_.isEmpty())
    {
        return false;
    }
    if(sysBase <= digitsNum)
    {
        int sysLastDigitCode = firstDigitCode + sysBase - 1;
        for(auto i = 0; i < numStr_.length(); i++)
        {
            QChar el = numStr_[i];
            int elCode = el.unicode();
            if(elCode > sysLastDigitCode)
            {
                return false;
            }
        }
    }
    else
    {
        int sysLastDigitCode = lastDigitCode;
        int sysLastLetterCode = firstLetterCode + sysBase - digitsNum;
        for(auto i = 0; i < numStr_.length(); i++)
        {
            QChar el = numStr_[i];
            int elCode = el.toUpper().unicode();
            if(elCode > sysLastDigitCode && (elCode < firstLetterCode || elCode > sysLastLetterCode))
            {
                return false;
            }
        }
    }
    return true;
}

qlonglong SystemNumber::GetDecimal() const{
    qlonglong decimal = 0;
    int strLen = numStr.length();
    for(auto i = 0; i < strLen; i++)
    {
        int el_code = numStr[i].toUpper().unicode();
        int el_value = el_code;
        if(el_code < lastDigitCode)
        {
            el_value -= firstDigitCode;
        }
        else
        {
            el_value -= (firstLetterCode - digitsNum);
        }
        int degree = strLen - i - 1;
        for(int j = 0; j < degree; j++)
        {
            el_value *= sysBase;
        }
        decimal += el_value;
    }
    return decimal;
}

//SystemNumber::SystemNumber(QString numStr_,unsigned int base)
//{
//    sysBase = base;
//    if(!setNumber(numStr_))
//    {
//        QErrorMessage erMessage;
//        erMessage.showMessage("Invalid input!");
//    }
//}

SystemNumber::SystemNumber(qlonglong num,unsigned base)
{
    sysBase = base;
    setNumber(num);
}

SystemNumber::SystemNumber(QString numStr_, unsigned base){
    numStr = numStr_;
    sysBase = base;
}

QChar SystemNumber::baseGetChar(int value, int base){
    if(value > base)
    {
        return '?';
    }
    else
    {
        if(value >= digitsNum)
        {
            return QChar(value - digitsNum + firstLetterCode);
        }
        else
        {
            return QChar(value + firstDigitCode);
        }
    }
}

QString SystemNumber::GetNumberInBase(const SystemNumber &number, unsigned int base){
    qlonglong num = number.GetDecimal();
    int remainder = num % base;
    QString resultStr;
    do{
        QChar digitChr = baseGetChar(remainder,base);
        resultStr.insert(0,digitChr);
        num /= base;
        remainder = num % base;
    }
    while(num != 0);
    return resultStr;
}

bool SystemNumber::setNumber(qlonglong num){
    int remainder = num % sysBase;
    QString resultStr;
    do{
        QChar digitChr = baseGetChar(remainder,sysBase);
        resultStr.insert(0,digitChr);
        num /= sysBase;
    }
    while(remainder != 0);
    numStr = resultStr;
    return true;
}

QString SystemNumber::getString() const{
    return numStr;
}
