cmake_minimum_required(VERSION 4.0)
project(Project)

set(CMAKE_CXX_STANDARD 20)

add_executable(Project main.cpp
        src/core/Driver.cpp
        src/core/Driver.h
        src/core/RideRequest.cpp
        src/core/RideRequest.h
        src/core/RegionQueue.cpp
        src/core/RegionQueue.h
        src/core/MatchEngine.cpp
        src/core/MatchEngine.h
        src/core/SpatialIndex.cpp
        src/core/SpatialIndex.h
        src/SystemManager.cpp
        src/SystemManager.h
        src/core/ActiveRide.h
        src/core/Map.h
        src/core/Map.cpp
)
