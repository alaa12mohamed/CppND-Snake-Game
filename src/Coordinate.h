#ifndef COORDINATE_H
#define COORDINATE_H

struct Coordinate
{
    Coordinate(const int x, const int y) : xCoordinate(x), yCoordinate(y){};

    // Getters
    int getXCoordinate() const { return xCoordinate; }
    int getYCoordinate() const { return yCoordinate; }
    bool operator==(const Coordinate &coordinate) const
    {
        return (xCoordinate == coordinate.xCoordinate && yCoordinate == coordinate.yCoordinate);
    }

private:
    int xCoordinate;
    int yCoordinate;
};

#endif