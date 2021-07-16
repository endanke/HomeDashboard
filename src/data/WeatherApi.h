#ifndef WeatherApi_H
#define WeatherApi_H

#include "HttpApi.h"

class WeatherApi : public HttpApi
{
public:
    void fetchWeather(const String& city);
    bool fetched = false;
    int tempC = 0;
    int feelsLikeC = 0;
};

#endif