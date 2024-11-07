#ifndef SHIP_HPP
#define SHIP_HPP

#include <iostream>
#include <vector>
#include "Structures.hpp"
#include "ShipSegment.hpp"

class Ship{
    private:
        std::vector<ShipSegment*> segments;
        int size;
        Orientation orientation;
        Coordinates coords;
        bool isPlaced;
        bool isDestroyed;
    public:
        Ship(int ShipSize);
        ~Ship();
        std::vector<ShipSegment*>& getSegments();
        int getSize() const;
        void setOrientation(Orientation shipOrientation);
        Orientation getOrientation() const;
        void setCoodrs(Coordinates coords);
        bool getIsPlaced() const;
        bool getIsDestroyed();
        void setStatus(bool status);
        void setIsPlaced(bool placed);
};

#endif // SHIP_HPP