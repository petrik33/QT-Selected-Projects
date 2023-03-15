#include "book.h"

Book::Book()
{

}

Book::Book(int _number, QString _name, int _year, int _pages)
{
    number = _number;
    name = _name;
    year = _year;
    pages = _pages;
}

Book::Book(QJsonObject &obj)
{
     load(obj);
}

bool Book::load(const QJsonObject &json)
{
    QString numberKey = "number";
    if(!json.contains(numberKey)){
        return false;
    }
    else number = json[numberKey].toInt();

    //...other parametrs should be loaded safely as well but well, it's easier this way

    name = json["name"].toString();
    year = json["year"].toInt();
    pages = json["pages"].toInt();

    QJsonArray authorsArray = json["authors"].toArray();
    int authorsNum = authorsArray.size();
    for(int i = 0; i < authorsNum;i++)
    {
        authors.push_back(authorsArray[i].toString());
    }

    return true;
}

bool Book::save(QJsonObject &json)
{
    json["number"] = number;
    json["name"] = name;
    json["year"] = year;
    json["pages"] = pages;
    QJsonArray authorsArray;
    for(const QString author : authors)
    {
        authorsArray.append(author);
    }
    json["authors"] = authorsArray;
    return true;
}
