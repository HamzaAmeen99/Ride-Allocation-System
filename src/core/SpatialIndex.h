#ifndef SPATIALINDEX_H
#define SPATIALINDEX_H

#include "RegionQueue.h"
#include "Map.h"
#include <vector>

class SpatialIndex {
public:
    int rows;       // number of rows in the grid
    int cols;       // number of columns in the grid
    float cellSize; // size of each cell

    std::vector<std::vector<RegionQueue>> grid;

    SpatialIndex(int rows, int cols, float cellSize);

    void addDriver(Driver* driver);          // place driver in correct cell
    std::vector<Driver*> getNearbyDrivers(float x, float y); // fetch drivers near a point
    void printGrid(const Map& map) const;

};

#endif