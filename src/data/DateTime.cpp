#include "DateTime.h"
#include <ezTime.h>

DateTime::DateTime(String location) {
    timezone = std::unique_ptr<Timezone>(new Timezone());
    timezone->setLocation(location);
}

String DateTime::getFinnishMonthName() {
    switch (timezone->month()) {
        case 1:
        return "Tammi";
        case 2:
        return "Helmi";
        case 3:
        return "Maalis";
        case 4:
        return "Huhti";
        case 5:
        return "Touko";
        case 6:
        return "Kesä";
        case 7:
        return "Heinä";
        case 8:
        return "Elo";
        case 9:
        return "Syys";
        case 10:
        return "Loka";
        case 11:
        return "Marras";
        case 12:
        return "Joulu";
    }
    return "Unknown";
}

int DateTime::timestampToMinutes(long arrivalTime) {
    auto offset = timezone->getOffset() * 60;
    auto now = timezone->now() + offset;
    if (arrivalTime < now) {
        return -1;
    }
    return (arrivalTime - now) / 60;
}

int DateTime::dayOfMonth() {
    return timezone->day();
}