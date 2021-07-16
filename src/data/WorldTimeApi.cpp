#include "WorldTimeApi.h"

void WorldTimeApi::fetchTime() {
  HTTPClient http;
  http.setTimeout(10000);
  
  String serverName = "http://worldtimeapi.org/api/timezone/Europe/Helsinki";
  http.begin(serverName.c_str());
  
  int httpResponseCode = http.GET();
  
  if (httpResponseCode == 200) {
    String payload = http.getString();
    Serial.println(payload);  
    DynamicJsonDocument doc(2048);
    deserializeJson(doc, payload);
    lastFetchedRemoteTime = doc["unixtime"].as<unsigned long>();
    lastFetchedTime = millis();
    
    Serial.println("Current time: ");
    Serial.println(currentTime());
    Serial.println(lastFetchedRemoteTime);
  } else {
    Serial.println("Failed to fetch time: " + httpResponseCode);
  }
  
  http.end();
}

unsigned long WorldTimeApi::currentTime() {
  return lastFetchedRemoteTime + (millis() - lastFetchedTime) / 1000;
}