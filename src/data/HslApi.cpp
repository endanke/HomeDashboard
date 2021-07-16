#include "HslApi.h"
#include "secrets.h"

long HslApi::fetchStationArrival(int id) {
  long arrivalTimeStamp = 0;
  HTTPClient http;
  http.setTimeout(30000);

  String serverName = "https://api.digitransit.fi/routing/v1/routers/hsl/index/graphql?digitransit-subscription-key=" + String(HSL_API_KEY);
  http.begin(serverName.c_str());
  
  String httpRequestData = "{stop(id:\"HSL:" + String(id) + "\"){name stoptimesWithoutPatterns{ realtimeArrival serviceDay }}}";
  int httpResponseCode = http.POST(httpRequestData);
  
  if (httpResponseCode > 0) {
    String payload = http.getString();
    DynamicJsonDocument doc(2048);
    deserializeJson(doc, payload);
    long serviceDay = doc["data"]["stop"]["stoptimesWithoutPatterns"][0]["serviceDay"].as<long>();
    long realtimeArrival = doc["data"]["stop"]["stoptimesWithoutPatterns"][0]["realtimeArrival"].as<long>();
    arrivalTimeStamp = serviceDay + realtimeArrival;
    Serial.println("Station info fetched");
  } else {
    Serial.println("Failed to fetch station info: " + httpResponseCode);
  }

  http.end();

  return arrivalTimeStamp;
}
