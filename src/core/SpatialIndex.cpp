#include "SpatialIndex.h"
#include <iomanip>
#include <cmath>

SpatialIndex::SpatialIndex(int r, int c, float size)
    : rows(r), cols(c), cellSize(size), grid(r, std::vector<RegionQueue>(c)) {}

// Add driver to correct cell based on coordinates
void SpatialIndex::addDriver(Driver* driver) {
    int row = std::min(int(driver->y / cellSize), rows - 1);
    int col = std::min(int(driver->x / cellSize), cols - 1);

    grid[row][col].addDriver(driver);
}

// Fetch all drivers in the cell containing (x,y) and neighboring cells
std::vector<Driver*> SpatialIndex::getNearbyDrivers(float x, float y) {
    std::vector<Driver*> result;

    int row = std::min(int(y / cellSize), rows - 1);
    int col = std::min(int(x / cellSize), cols - 1);

    // check neighboring cells (3x3 grid around point)
    for (int i = std::max(0, row - 1); i <= std::min(rows - 1, row + 1); ++i) {
        for (int j = std::max(0, col - 1); j <= std::min(cols - 1, col + 1); ++j) {
            Driver* current = grid[i][j].head;
            while (current != nullptr) {
                if (current->status == DriverStatus::Available)
                    result.push_back(current);
                current = current->next;
            }
        }
    }

    return result;
}

#include <iostream>

void SpatialIndex::printGrid(const Map& map) const {
    std::cout << "\n---- Spatial Grid ----\n";

    for (int i = rows - 1; i >= 0; --i) {   // top to bottom
        for (int j = 0; j < cols; ++j) {

            bool printed = false;

            // 1️⃣ Check for location in this cell
            for (const auto& loc : map.getAllLocations()) {
                int r = int(loc.y / cellSize);
                int c = int(loc.x / cellSize);

                if (r == i && c == j) {
                    std::cout << std::setw(8) << loc.name.substr(0, 5);
                    printed = true;
                    break;
                }
            }

            // 2️⃣ Check for driver
            if (!printed && grid[i][j].head != nullptr) {
                std::cout << std::setw(8) << "D";
                printed = true;
            }

            // 3️⃣ Empty cell
            if (!printed) {
                std::cout << std::setw(8) << ".";
            }
        }
        std::cout << "\n";
    }
}
