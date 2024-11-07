#include "DoubleDamage.hpp"

DoubleDamage::DoubleDamage(GameField& field):field(field) {};


void DoubleDamage::useAbility() {
    std::cout << "Double Damage is applying." << std::endl;
    field.setDoubleDamage();
}