#ifndef SYSTEMMANAGER_H
#define SYSTEMMANAGER_H

#include <vector>

#include "core/Map.h"
#include "core/Driver.h"
#include "core/RideRequest.h"
#include "core/SpatialIndex.h"
#include "core/MatchEngine.h"
#include "core/ActiveRide.h"

class SystemManager {
public:
    SystemManager();

    void run();

    void registerDriver();
    void createRideRequest();
    void matchRide();

    void showDrivers();
    void showGrid();
    void showActiveRides();   // NEW

private:
    // Stored data
    std::vector<Driver*> drivers;
    std::vector<RideRequest*> requests;   // pending ride requests
    std::vector<ActiveRide> activeRides;  // NEW: multiple active rides

    SpatialIndex index;
    MatchEngine engine;
    Map cityMap;

    int nextDriverId;
    int nextRequestId;

    // Helpers
    Driver* findDriverById(int id);
    void clearInput();
    void completeRide();
};

#endif
