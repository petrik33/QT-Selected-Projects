#ifndef FLIGHTENUMCLASS_H
#define FLIGHTENUMCLASS_H

#include <QStringList>

class FlightEnumClass
{
public:
    enum FLIGHT_ENUM {NUMBER = 0,DESTINATION,DEPARTURE,ARRIVAL,PASSENGERS,ENUM_SIZE};
    static const QStringList FLIGHT_ENUM_NAMES;
private:
    explicit FlightEnumClass();
};

typedef FlightEnumClass::FLIGHT_ENUM FLIGHT;

#endif // FLIGHTENUMCLASS_H
