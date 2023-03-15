#ifndef FLIGHTDATA_H
#define FLIGHTDATA_H

#include <flightenumclass.h>
#include <QString>
#include <QDateTime>
#include <QVector>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

const QString dateFormat = "dd.MM.yyyy hh:mm";

struct Person{
    QString _name;
    QString _docID;
    Person(QString name, QString docID){
        _name = name;
        _docID = docID;
    }
};

class FlightData
{
public:
    FlightData();
    FlightData(
            QString number,
            QString destination,
            QDateTime departure,
            QDateTime arrival
            );
    FlightData(QJsonObject& json);
    QString _number;
    QString _destination;
    QDateTime _departure;
    QDateTime _arrival;
    QVector<Person*> _passengers;
    bool load(const QJsonObject& json);
    bool save(QJsonObject& json);
};

#endif // FLIGHTDATA_H
