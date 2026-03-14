#ifndef MATCHENGINE_H
#define MATCHENGINE_H

#include "Driver.h"
#include "SpatialIndex.h"
#include "RideRequest.h"

class MatchEngine {
public:
    MatchEngine() = default;

    // Driver* selectBestDriver(RegionQueue& regionQueue, RideRequest& request, float alpha, float beta, float gamma);
    Driver* selectBestDriver(SpatialIndex& index, RideRequest& request, float alpha, float beta, float gamma);

private:
    float computeScore(Driver* driver, RideRequest& request, float alpha, float beta, float gamma);
};

#endif
