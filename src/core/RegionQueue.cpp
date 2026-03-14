#include "RegionQueue.h"

RegionQueue::RegionQueue() : head(nullptr), tail(nullptr) {}

// Add driver to the end of the queue
void RegionQueue::addDriver(Driver* driver) {
    driver->next = nullptr;
    driver->prev = tail;

    if (tail != nullptr)
        tail->next = driver;
    else
        head = driver;  // first driver in the queue

    tail = driver;
}

// Print all drivers in the queue
void RegionQueue::printQueue() {
    Driver* current = head;
    while (current != nullptr) {
        current->printInfo();
        current = current->next;
    }
}

void RegionQueue::removeDriver(Driver* driver) {
    if (!driver) return;

    if (driver->prev)
        driver->prev->next = driver->next;
    else
        head = driver->next;  // driver was head

    if (driver->next)
        driver->next->prev = driver->prev;
    else
        tail = driver->prev;  // driver was tail

    driver->next = nullptr;
    driver->prev = nullptr;
}
