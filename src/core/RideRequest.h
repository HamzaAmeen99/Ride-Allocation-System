#ifndef RIDEREQUEST_H
#define RIDEREQUEST_H

#include <string>

enum class RidePriority {
    Normal,
    Premium
};

class RideRequest {
public:
    int id;
    float originX, originY;
    float destX, destY;
    std::string timestamp;
    RidePriority priority;

    RideRequest(int id, float ox, float oy, float dx, float dy, std::string ts, RidePriority p);

    void printInfo();
};

#endif
