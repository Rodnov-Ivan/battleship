#ifndef FIELDDRAWER_HPP
#define FIELDDRAWER_HPP

#include "Ship.hpp"
#include "GameField.hpp"
#include "Structures.hpp"
#include <vector>
#include <iostream>

class FieldDrawer{
    public:
        void draw(GameField& field, bool showShips) const;
};

#endif // FIELDDRAWER_HPP
