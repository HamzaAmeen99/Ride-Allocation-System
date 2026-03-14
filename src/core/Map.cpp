#include "Map.h"
#include <iostream>

Map::Map() {
    locations = {
        {1, "F-7 Markaz", 2.0f, 8.0f},
        {2, "F-10 Markaz", 4.0f, 9.0f},
        {3, "G-9 Markaz", 5.0f, 7.0f},
        {4, "Blue Area", 6.0f, 6.0f},
        {5, "I-8 Markaz", 7.0f, 4.0f},
        {6, "Centaurus Mall", 6.5f, 6.8f},
        {7, "FAST University", 8.0f, 2.0f}
    };
}

void Map::showLocations() const {
    std::cout << "\n---- Available Locations (Islamabad) ----\n";
    for (const auto& loc : locations) {
        std::cout << loc.id << ". " << loc.name << "\n";
    }
}

const MapLocation* Map::getLocationById(int id) const {
    for (const auto& loc : locations) {
        if (loc.id == id)
            return &loc;
    }
    return nullptr;
}

const std::vector<MapLocation>& Map::getAllLocations() const {
    return locations;
}

const MapLocation* Map::getLocationByCoordinates(float x, float y) const {
    for (const auto& loc : locations) {
        if (loc.x == x && loc.y == y)
            return &loc;
    }
    return nullptr;
}
