#ifndef WorldTimeApi_H
#define WorldTimeApi_H

#include "HttpApi.h"

class WorldTimeApi : public HttpApi
{
public:
    void fetchTime();
    unsigned long currentTime();

    unsigned long lastFetchedRemoteTime = 0;
    unsigned long lastFetchedTime = 0;
};

#endif