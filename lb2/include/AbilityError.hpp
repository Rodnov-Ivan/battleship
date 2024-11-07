#ifndef ABILITYERROR_HPP
#define ABILITYERROR_HPP

#include "Structures.hpp"

class AbilityError : public std::runtime_error{
public:
    AbilityError(const std::string &msg) : std::runtime_error(msg){}
};

#endif //NOABILITYERROR_HPP
