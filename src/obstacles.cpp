#include "Obstacles.h"
#include <memory>
#include "Coordinate.h"

Obstacles::Obstacles()
{
    // Initialising unique pointer
    _coordinates = std::unique_ptr<std::vector<Coordinate>>(new std::vector<Coordinate>);
}

void Obstacles::addCoordinate(const Coordinate &&coordinate)
{
    _coordinates->emplace_back(coordinate);
}

bool Obstacles::ObstacleCell(const Coordinate &&coordinate)
{
    for (const Coordinate &_coordinate : *_coordinates)
    {
        if (_coordinate == coordinate)
        {
            return true;
        }
    }
    return false;
}

int Obstacles::count() const
{
    return _coordinates->size();
}

const std::vector<Coordinate> &Obstacles::getCoordinates() const
{
    return *_coordinates; // Copy will not be made due to RVO
}