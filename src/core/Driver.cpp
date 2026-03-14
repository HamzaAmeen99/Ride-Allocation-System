#include "Driver.h"
#include <iostream>

Driver::Driver(int id, float rating, float xCoord, float yCoord)
    : id(id), rating(rating), idleTime(0),
      status(DriverStatus::Available), x(xCoord), y(yCoord),
      next(nullptr), prev(nullptr) {}

void Driver::printInfo() {
    std::string stat;
    switch(status) {
        case DriverStatus::Available: stat = "Available"; break;
        case DriverStatus::OnTrip: stat = "On Trip"; break;
        case DriverStatus::Offline: stat = "Offline"; break;
    }
    std::cout << "Driver ID: " << id
              << ", Rating: " << rating
              << ", Status: " << stat
              << ", Idle Time: " << idleTime << " mins"
              << ", Location: (" << x << "," << y << ")\n";
}

void Driver::setStatus(DriverStatus newStatus) {
    status = newStatus;
}