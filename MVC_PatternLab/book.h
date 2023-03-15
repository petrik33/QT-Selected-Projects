#ifndef BOOK_H
#define BOOK_H

#include <QString>
#include <QStringList>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

class Book
{
public:
    Book();
    Book(int number,QString name,int year,int pages);
    Book(QJsonObject& obj);
    int number;
    QString name;
    QStringList authors;
    int year;
    int pages;
    bool load(const QJsonObject& json);
    bool save(QJsonObject& json);
};

#endif // BOOK_H
