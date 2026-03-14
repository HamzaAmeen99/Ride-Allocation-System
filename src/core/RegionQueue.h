#ifndef REGIONQUEUE_H
#define REGIONQUEUE_H

#include "Driver.h"

class RegionQueue {
public:
    Driver* head;
    Driver* tail;

    RegionQueue();

    void addDriver(Driver* driver);  // insert driver at the end
    void printQueue();                // to test the queue
    void removeDriver(Driver* driver); // remove a driver from the queue
};

#endif
