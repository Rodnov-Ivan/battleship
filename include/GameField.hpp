#ifndef GAMEFIELD_HPP
#define GAMEFIELD_HPP

#include "Ship.hpp"
#include "Structures.hpp"
#include <vector>
#include <iostream>

class GameField{
    private:
        int height;
        int width;
        std::vector<FieldCell> field;
    public:
        GameField(int fieldHeight, int fieldWidth);
        GameField(const GameField& other);
        GameField(GameField&& other);
        GameField& operator=(const GameField& other);
        GameField& operator=(GameField&& other);
        void placeShip(Ship* ship, Coordinates coords, Orientation orientation);
        void attackCell(Coordinates coords);
        bool checkAttackCoord(Coordinates coord);
        bool checkFieldBorders(Ship* ship);
        bool checkShipsContact(Ship* ship);
};

#endif GAMEFIELD_HPP