#ifndef SHIPMANAGER_HPP
#define SHIPMANAGER_HPP

#include "Ship.hpp"
#include "Structures.hpp"
#include <iostream>
#include <vector>

class ShipManager{
    private:
        std::vector<Ship*> ships;
        std::vector<int> sizeShips;
    public:
        ShipManager(std::vector<int> sizes);
        ~ShipManager();
        std::vector<Ship*> getAllShips();
        Ship* getShipByCoordinates(Coordinates coords);
        void printShipsInfo();
};

#endif SHIPMANAGER_HPP