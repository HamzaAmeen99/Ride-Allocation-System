#include "MatchEngine.h"
#include <cmath>
#include <limits>

// Compute score using real distance between driver and ride request origin
float MatchEngine::computeScore(Driver* driver, RideRequest& request, float alpha, float beta, float gamma) {
    float dx = driver->x - request.originX;
    float dy = driver->y - request.originY;
    float distance = std::sqrt(dx * dx + dy * dy);

    return alpha * distance + beta * (1 - driver->rating / 5.0) - gamma * driver->idleTime;
}

Driver* MatchEngine::selectBestDriver(SpatialIndex& index, RideRequest& request, float alpha, float beta, float gamma) {
    Driver* bestDriver = nullptr;
    float bestScore = std::numeric_limits<float>::max();

    // get nearby drivers from spatial index
    std::vector<Driver*> nearbyDrivers = index.getNearbyDrivers(request.originX, request.originY);

    for (Driver* driver : nearbyDrivers) {
        float score = computeScore(driver, request, alpha, beta, gamma);
        if (score < bestScore) {
            bestScore = score;
            bestDriver = driver;
        }
    }

    return bestDriver;
}
