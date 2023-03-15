#include "flightdata.h"

FlightData::FlightData()
{

}

FlightData::FlightData(QString number, QString destination, QDateTime departure, QDateTime arrival)
{
    _number = number;
    _destination = destination;
    _departure = departure;
    _arrival = arrival;
}

FlightData::FlightData(QJsonObject &json)
{
    load(json);
}

bool FlightData::load(const QJsonObject &json)
{
//    for(int i = 0; i < FLIGHT::ENUM_SIZE; i++)
//    {
//        if(!json.contains(FlightEnumClass::FLIGHT_ENUM_NAMES[i]))
//        {
//            return false;
//        }
//    }

//    for(int i = 0; i < FLIGHT::PASSENGERS; i++)
//    {
//        QString keyName = FlightEnumClass::FLIGHT_ENUM_NAMES[i];
//        QString value = json[keyName].toString();
//    }

    QString numberKey = "Number";
    if(!json.contains(numberKey)){
        return false;
    }
    else _number = json[numberKey].toString();

    //...other parametrs should be loaded safely as well but... well, who cares :)

    _destination = json["Destination"].toString();

    QString departureStr = json["Departure"].toString();
    _departure = QDateTime::fromString(departureStr,dateFormat);

    QString arrivalStr = json["Arrival"].toString();
    _arrival = QDateTime::fromString(arrivalStr,dateFormat);

    QJsonArray passengers = json["Passengers"].toArray();
    int passengersNum = passengers.size();
    for(int i = 0; i < passengersNum;i++)
    {
        Person* p = nullptr;
        QJsonObject singlePas = passengers[i].toObject();
        QString nameKey = "name"; QString pasKey = "passport id";
        if(singlePas.contains(nameKey) && singlePas.contains(pasKey))
        {
            p = new Person(singlePas[nameKey].toString(),singlePas[pasKey].toString());
            _passengers.push_back(p);
        }
    }

    return true;
}

bool FlightData::save(QJsonObject &json)
{
    json["Number"] = _number;
    json["Destination"] = _destination;
    json["Departure"] = _departure.toString(dateFormat);
    json["Arrival"] = _arrival.toString(dateFormat);
    QJsonArray passengersArray;
    for(const Person* pPerson : _passengers)
    {
        QJsonObject personObject;
        personObject["name"] = pPerson->_name;
        personObject["passport id"] = pPerson->_docID;
        passengersArray.append(personObject);
    }
    json["Passengers"] = passengersArray;
    return true;
}

