#ifndef HslApi_H
#define HslApi_H

#include "HttpApi.h"

class HslApi : public HttpApi
{
public:
    long fetchBusStationArrival(int id);
    int fetchBikeStationAvailability(int id);
};

#endif