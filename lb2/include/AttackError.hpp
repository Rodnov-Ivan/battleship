#ifndef ATTACKERROR_HPP
#define ATTACKERROR_HPP

#include "Structures.hpp"

class AttackError : public std::runtime_error{
public:
    AttackError(const std::string &msg) : std::runtime_error(msg){}
};


#endif // ATTACKERROR_HPP
