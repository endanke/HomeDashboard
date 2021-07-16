#ifndef DateTime_H
#define DateTime_H

#include <Arduino.h>
#include <memory>

class Timezone;

class DateTime {
public:
    DateTime(String location);

    String getFinnishMonthName();
    int timestampToMinutes(long arrivalTime);
    int dayOfMonth();

private:
    std::unique_ptr<Timezone> timezone;
};

#endif