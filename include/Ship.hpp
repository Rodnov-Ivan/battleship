#ifndef SHIP_HPP
#define SHIP_HPP

#include <iostream>
#include <vector>
#include "Structures.hpp"

class Ship{
    private:
        std::vector<ShipSegment*> segments;
        int size;
        Orientation orientation;
        Coordinates coords;
        bool isPlaced;
    public:
        Ship(int ShipSize);
        ~Ship();
        void initSegments();
        std::vector<ShipSegment*> getSegments();
        int getSize() const;
        void setOrientation(Orientation shipOrientation);
        Orientation getOrientation() const;
        void setCoodrs(Coordinates coords);
        bool getIsPlaced() const;
        void setIsPlaced(bool placed);
};

#endif // SHIP_HPP