#ifndef MAP_H
#define MAP_H

#include <string>
#include <vector>

struct MapLocation {
    int id;
    std::string name;
    float x;
    float y;
};

class Map {
public:
    Map();

    void showLocations() const;
    const MapLocation* getLocationById(int id) const;
    const std::vector<MapLocation>& getAllLocations() const;
    const MapLocation* getLocationByCoordinates(float x, float y) const;

private:
    std::vector<MapLocation> locations;
};

#endif
