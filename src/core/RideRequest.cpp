#include "RideRequest.h"
#include <iostream>

RideRequest::RideRequest(int id, float ox, float oy, float dx, float dy, std::string ts, RidePriority p)
    : id(id), originX(ox), originY(oy), destX(dx), destY(dy), timestamp(ts), priority(p) {}

void RideRequest::printInfo() {
    std::string pri = (priority == RidePriority::Normal) ? "Normal" : "Premium";
    std::cout << "RideRequest ID: " << id 
              << ", Origin: (" << originX << "," << originY << ")"
              << ", Destination: (" << destX << "," << destY << ")"
              << ", Timestamp: " << timestamp
              << ", Priority: " << pri << "\n";
}
