#include "WeatherApi.h"

void WeatherApi::fetchWeather(const String& city) {
  const auto longFetch = 1000 * 60;
  const auto shortFetch = 1000 * 3;
  const auto timeDiff = millis() - lastFetchTime;
  if (!fetched && timeDiff < shortFetch) {
    return;
  } else if (timeDiff < longFetch) {
    return;
  }
  lastFetchTime = millis();

  HTTPClient http;
  http.setTimeout(10000);
  
  String serverName = "https://wttr.in/" + city + "?format=j1";
  http.begin(serverName.c_str());
  
  int httpResponseCode = http.GET();
  
  if (httpResponseCode == 200) {
    String payload = http.getString();
    DynamicJsonDocument doc(2048);
    deserializeJson(doc, payload);
    tempC = doc["current_condition"][0]["temp_C"];
    feelsLikeC = doc["current_condition"][0]["FeelsLikeC"];
    fetched = true;

    Serial.println("Current temperature: " + doc["current_condition"][0]["temp_C"].as<String>());
  } else {
    Serial.println("Failed to fetch weather: " + httpResponseCode);
  }
  
  http.end();
}