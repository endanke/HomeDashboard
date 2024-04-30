#ifndef Composer_H
#define Composer_H

#include <Arduino.h>
#include <memory>

class HslApi;
class WeatherApi;
class DateTime;

class Composer
{
public:
    Composer();
    ~Composer();
    void setup();
    void loop();

    String displayText;

private:
    void fetchData();
    std::unique_ptr<HslApi> hslApi;
    std::unique_ptr<WeatherApi> weatherApi;
    std::unique_ptr<DateTime> dateTime;
    
    unsigned long lastTime = 0;
    unsigned long timerDelay = 30000;
    bool fetched = false;
    long arrivalStationA = 0;
    long arrivalStationB = 0;
    int bikeStationAvailability = 0;
    int feelsLikeC = 0;
    int tempC = 0;
};

#endif