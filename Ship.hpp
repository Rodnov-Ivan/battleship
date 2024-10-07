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
    public:
        Ship(int ShipSize);

        ~Ship();

        std::vector<ShipSegment*> getSegments();

        int getSize() const;

        void changeOrientation();

        Orientation getOrientation() const;

        void setCoodrs(Coordinates coords);
};

#endif SHIP_HPP