#ifndef FIELDDRAWER_HPP
#define FIELDDRAWER_HPP

#include "Ship.hpp"
#include "GameField.hpp"
#include "Structures.hpp"
#include "ShipSegment.hpp"
#include <vector>
#include <iostream>

class FieldDrawer{
    public:
        void draw(GameField& field, bool showShips = false) const;
};

#endif // FIELDDRAWER_HPP