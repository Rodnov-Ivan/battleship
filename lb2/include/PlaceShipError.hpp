#ifndef PLACESHIPERROR_HPP
#define PLACESHIPERROR_HPP

#include "Structures.hpp"

class PlaceShipError : public std::runtime_error{
public:
    PlaceShipError(const std::string &msg) : std::runtime_error(msg){}
};


#endif //PLACESHIPERROR_HPP
