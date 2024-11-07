#ifndef ABILITY_HPP
#define ABILITY_HPP

#include "GameField.hpp"
#include "Structures.hpp"
#include <chrono>
#include <random>

class Ability{
public:
    virtual void useAbility() = 0;
    virtual ~Ability() {}
};

#endif //ABILITY_HPP