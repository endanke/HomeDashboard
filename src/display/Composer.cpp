#include "Composer.h"
#include <ezTime.h>
#include "../data/WeatherApi.h"
#include "../data/HslApi.h"
#include "../data/DateTime.h"
#include "secrets.h"

namespace {
    String arrivalText(String name, int arrivalMins) {
        if (arrivalMins < 0) {
            return name + ": " + "?";
        }
        String result = name + ": \t" + String(arrivalMins) + "m";
        return result;
    }
}

Composer::Composer() {
    weatherApi = std::unique_ptr<WeatherApi>(new WeatherApi());
    hslApi = std::unique_ptr<HslApi>(new HslApi());
    dateTime = std::unique_ptr<DateTime>(new DateTime("Europe/Helsinki"));
}

Composer::~Composer() {}

void Composer::setup() {
    Serial.println("Waiting for time sync");
	waitForSync();
}

void Composer::loop() {
    if (!fetched || (millis() - lastTime) > timerDelay) {
        fetchData();
    }

    displayText = String(dateTime->dayOfMonth()) + ". " +  dateTime->getFinnishMonthName() + "kuu\n";
    displayText += arrivalText(STATION_A_DIRECTION, dateTime->timestampToMinutes(arrivalStationA)) + "\n";
    displayText += arrivalText(STATION_B_DIRECTION, dateTime->timestampToMinutes(arrivalStationB)) + "\n";
    if (weatherApi->fetched) {
        displayText += "Temperature: " + String(tempC) + "C\n";
        displayText += "Feels like: " + String(feelsLikeC) + "C";
    } else {
        displayText += "Waiting for weather";
    }
}

void Composer::fetchData() {
    Serial.println("Fetching weather");
    weatherApi->fetchWeather("Helsinki");
    feelsLikeC = weatherApi->feelsLikeC;
    tempC = weatherApi->tempC;

    Serial.println("Fetching stations");
    long newArrival = hslApi->fetchStationArrival(STATION_A_ID); 
    if (newArrival > 0) {
        arrivalStationA = newArrival;
    }
    newArrival = hslApi->fetchStationArrival(STATION_B_ID); 
    if (newArrival > 0) {
        arrivalStationB = newArrival;
    }
    lastTime = millis();
    fetched = true;
}
