#ifndef GAMEFIELD_HPP
#define GAMEFIELD_HPP

#include "Ship.hpp"
#include "Structures.hpp"
#include "ShipSegment.hpp"
#include "PlaceShipError.hpp"
#include "AttackError.hpp"
#include <vector>
#include <iostream>
#include <algorithm>

class GameField{
    private:
        int height;
        int width;
        std::vector<FieldCell> field;
        using AttackFunction = void (GameField::*)(ShipSegment* shipSegment);
        AttackFunction orginalAttack;
        void doubleDamageAttack(ShipSegment* shipSegment);
        void averageAttack(ShipSegment* shipSegment);

    public:
        GameField(int fieldHeight, int fieldWidth);
        GameField(const GameField& other);
        GameField(GameField&& other);
        GameField& operator=(const GameField& other);
        GameField& operator=(GameField&& other);
        ~GameField();

        int getWidth();
        int getHeight();
        const std::vector<FieldCell>& getField() const;
        bool checkAttackCoord(Coordinates coord);
        bool checkFieldBorders(Ship* ship);
        bool checkShipsContact(Ship* ship);
        void placeShip(Ship* ship, Coordinates coords, Orientation orientation);
        bool attackCell(Coordinates coords);
        void removeShip(Ship* ship);
        void setDoubleDamage();
};

#endif // GAMEFIELD_HPP