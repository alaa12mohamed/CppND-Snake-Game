#include "Boosters.h"
#include <memory>
#include "Coordinate.h"

Boosters::Boosters()
{
    // Initialising unique pointer
    _coordinates = std::unique_ptr<std::vector<Coordinate>>(new std::vector<Coordinate>);
}

void Boosters::addCoordinate(const Coordinate &&coordinate)
{
    _coordinates->emplace_back(coordinate);
}

bool Boosters::BoosterCell(const Coordinate &&coordinate) const
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

void Boosters::deleteBoosterCellAt(const Coordinate &&coordinate)
{
    /// Early exit.
    if (_coordinates->size() == 0)
    {
        return;
    }
    for (auto it = _coordinates->begin(); it != _coordinates->end();)
    {
        if (*it == coordinate)
        {
            it = _coordinates->erase(it);
        }
        else
        {
            ++it;
        }
    }
}

const std::vector<Coordinate> &Boosters::getCoordinates() const
{
    return *_coordinates; // Copy will not be made due to RVO
}

int Boosters::count() const
{
    return _coordinates->size();
}
