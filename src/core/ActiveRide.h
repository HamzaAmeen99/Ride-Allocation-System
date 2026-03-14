#ifndef ACTIVERIDE_H
#define ACTIVERIDE_H

#include "RideRequest.h"
#include "Driver.h"

// Represents one active ride (ride + assigned driver)
struct ActiveRide {
    RideRequest* ride;
    Driver* driver;
};

#endif
