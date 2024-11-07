#ifndef ABILITYMANAGER_HPP
#define ABILITYMANAGER_HPP

#include "Ability.hpp"
#include "AbilityError.hpp"
#include <queue>

class AbilityManager {
private:
    std::vector<Ability*> abilitySet;
    std::queue<Ability*> abilities;

public:
    AbilityManager(GameField& field);
    ~AbilityManager();
    void methodAbility();
    void addRandomAbility();
};

#endif //ABILITYMANAGER_HPP