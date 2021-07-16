#ifndef HttpApi_H
#define HttpApi_H

#include <HTTPClient.h>
#include <ArduinoJSON.h>

class HttpApi
{
protected:
  long lastFetchTime = 0;
};

#endif