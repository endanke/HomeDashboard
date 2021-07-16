#ifndef HslApi_H
#define HslApi_H

#include "HttpApi.h"

class HslApi : public HttpApi
{
public:
    long fetchStationArrival(int id);
};

#endif