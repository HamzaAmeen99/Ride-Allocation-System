#include "SystemManager.h"
#include <iostream>

SystemManager::SystemManager()
    : index(10, 10, 1.0f),
      nextDriverId(1),
      nextRequestId(1)
{
    std::cout << "SystemManager initialized.\n";
}

void SystemManager::run() {
    int choice;

    while (true) {
        std::cout << "\n---- Ride Allocation System ----\n";
        std::cout << "1. Register Driver\n";
        std::cout << "2. Create Ride Request\n";
        std::cout << "3. Match Ride\n";
        std::cout << "4. Show All Drivers\n";
        std::cout << "5. Show Spatial Grid\n";
        std::cout << "5. Show Active Rides\n";
        std::cout << "7. Complete Ride\n";
        std::cout << "8. Exit\n";
        std::cout << "Enter choice: ";

        std::cin >> choice;

        if (std::cin.fail()) {
            clearInput();
            std::cout << "Invalid input. Please enter a number.\n";
            continue;
        }

        if (choice == 1) registerDriver();
        else if (choice == 2) createRideRequest();
        else if (choice == 3) matchRide();
        else if (choice == 4) showDrivers();
        else if (choice == 5) showGrid();
        else if (choice == 6) showActiveRides();
        else if (choice == 7) completeRide();
        else if (choice == 8) break;
        else std::cout << "Invalid choice.\n";
    }
}

void SystemManager::registerDriver() {
    int id, region, locationId;
    float rating;

    std::cout << "\nRegistering new driver...\n";

    std::cout << "Enter driver ID: ";
    std::cin >> id;

    if (std::cin.fail()) {
        clearInput();
        std::cout << "Invalid ID input.\n";
        return;
    }

    if (findDriverById(id)) {
        std::cout << "Driver with this ID already exists.\n";
        return;
    }

    std::cout << "Enter rating (0-5): ";
    std::cin >> rating;

    if (std::cin.fail() || rating < 0 || rating > 5) {
        clearInput();
        std::cout << "Invalid rating.\n";
        return;
    }

    // 📍 LOCATION SELECTION
    cityMap.showLocations();
    std::cout << "Select driver starting location ID: ";
    std::cin >> locationId;

    const MapLocation* loc = cityMap.getLocationById(locationId);
    if (!loc) {
        std::cout << "Invalid location selection.\n";
        return;
    }

    Driver* d = new Driver(id, rating, loc->x, loc->y);
    drivers.push_back(d);
    index.addDriver(d);

    std::cout << "Driver registered at " << loc->name << " successfully!\n";
}

void SystemManager::createRideRequest() {
    int originId, destId, p;

    cityMap.showLocations();

    std::cout << "Select origin location ID: ";
    std::cin >> originId;

    const MapLocation* origin = cityMap.getLocationById(originId);
    if (!origin) {
        std::cout << "Invalid origin location.\n";
        return;
    }

    std::cout << "Select destination location ID: ";
    std::cin >> destId;

    const MapLocation* dest = cityMap.getLocationById(destId);
    if (!dest) {
        std::cout << "Invalid destination location.\n";
        return;
    }

    // std::cout << "Priority? (0 = Normal, 1 = Premium): ";
    // std::cin >> p;

    // RidePriority pr = (p == 0) ? RidePriority::Normal : RidePriority::Premium;

    RideRequest* req = new RideRequest(
        nextRequestId++,
        origin->x, origin->y,
        dest->x, dest->y,
        "NOW",
        RidePriority::Normal
    );

    requests.push_back(req);

    std::cout << "Ride request created from "
              << origin->name << " to " << dest->name << "\n";
}

void SystemManager::matchRide() {
    if (requests.empty()) {
        std::cout << "No ride requests pending.\n";
        return;
    }

    RideRequest* req = requests.back();

    Driver* best =
        engine.selectBestDriver(index, *req, 1.0f, 1.0f, 1.0f);

    if (best == nullptr) {
        std::cout << "No available drivers nearby.\n";
        return;
    }

    std::cout << "\nBest driver found:\n";
    best->printInfo();

    best->setStatus(DriverStatus::OnTrip);

    // 🔴 IMPORTANT CHANGE
    ActiveRide ar;
    ar.ride = req;
    ar.driver = best;
    activeRides.push_back(ar);

    requests.pop_back();

    std::cout << "Driver assigned. Ride is now active!\n";
}

void SystemManager::showActiveRides() {
    if (activeRides.empty()) {
        std::cout << "No active rides.\n";
        return;
    }

    std::cout << "\n---- Active Rides ----\n";
    for (const ActiveRide& ar : activeRides) {
        std::cout << "Ride ID: " << ar.ride->id
                  << " -> Driver ID: " << ar.driver->id << "\n";
    }
}

void SystemManager::showDrivers() {
    if (drivers.empty()) {
        std::cout << "No drivers registered.\n";
        return;
    }

    std::cout << "\n---- Registered Drivers ----\n";

    for (Driver* d : drivers) {
        const MapLocation* loc =
            cityMap.getLocationByCoordinates(d->x, d->y);

        d->printInfo();

        if (loc) {
            std::cout << "   -> Location: " << loc->name << "\n";
        } else {
            std::cout << "   -> Location: Unknown\n";
        }
    }
}

void SystemManager::showGrid() {
    index.printGrid(cityMap);
}

void SystemManager::clearInput() {
    std::cin.clear();
    std::cin.ignore(1000, '\n');
}

Driver* SystemManager::findDriverById(int id) {
    for (Driver* d : drivers) {
        if (d->id == id)
            return d;
    }
    return nullptr;
}

void SystemManager::completeRide() {
    if (activeRides.empty()) {
        std::cout << "No active rides to complete.\n";
        return;
    }

    int rideId;
    std::cout << "Enter Ride ID to complete: ";
    std::cin >> rideId;

    if (std::cin.fail()) {
        clearInput();
        std::cout << "Invalid Ride ID input.\n";
        return;
    }

    // Find the active ride
    for (auto it = activeRides.begin()
        ; it != activeRides.end(); ++it) {
        if (it->ride->id == rideId) {

            Driver* driver = it->driver;
            RideRequest* ride = it->ride;

            // 1️⃣ Move driver to destination
            driver->x = ride->destX;
            driver->y = ride->destY;

            // 2️⃣ Ask for rating
            float stars;
            std::cout << "Rate the driver (1-5): ";
            std::cin >> stars;

            if (std::cin.fail() || stars < 1 || stars > 5) {
                clearInput();
                std::cout << "Invalid rating.\n";
                return;
            }

            // 3️⃣ Update driver rating (simple average)
            driver->rating = (driver->rating + stars) / 2.0f;

            // 4️⃣ Update driver status
            driver->setStatus(DriverStatus::Available);

            // 5️⃣ Reinsert driver into spatial grid
            index.addDriver(driver);

            // 6️⃣ Remove active ride
            activeRides.erase(it);

            std::cout << "Ride completed successfully!\n";
            std::cout << "Updated driver info:\n";
            driver->printInfo();

            return;
        }
    }

    std::cout << "Ride ID not found among active rides.\n";
}
