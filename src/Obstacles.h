#ifndef OBSTACLES_H
#define OBSTACLES_H

#include <memory>
#include <vector>
#include "Coordinate.h"

class Obstacles
{
    public:
    Obstacles();

    void addCoordinate(const Coordinate &&coordinate);
    bool ObstacleCell(const Coordinate &&coordinate);
    int count() const;

    const std::vector<Coordinate> &getCoordinates() const;

    private:
    std::unique_ptr<std::vector<Coordinate>> _coordinates;
};

#endif