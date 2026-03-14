#ifndef DRIVER_H
#define DRIVER_H

enum class DriverStatus {
    Available,
    OnTrip,
    Offline
};

class Driver {
public:
    int id;
    //int regionId;    // optional, can still keep for region-based queues
    float rating;
    int idleTime;
    DriverStatus status;

    float x, y;      // new: driver coordinates

    Driver* next;
    Driver* prev;

    Driver(int id, float rating, float xCoord, float yCoord);

    void printInfo();
    void setStatus(DriverStatus newStatus);
};

#endif
