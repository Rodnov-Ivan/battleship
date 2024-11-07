#include "AbilityManager.hpp"
#include "DoubleDamage.hpp"
#include "Scanner.hpp"
#include "RandomHit.hpp"

AbilityManager::AbilityManager(GameField& field){
    abilitySet.push_back(new DoubleDamage(field));
    abilitySet.push_back(new Scanner(field));
    abilitySet.push_back(new RandomHit(field));
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    auto rng = std::default_random_engine(seed);
    std::shuffle(abilitySet.begin(), abilitySet.end(), rng);

    for (auto ability : abilitySet) {
        abilities.push(ability);
    }
}

AbilityManager::~AbilityManager() {
    while (!abilities.empty()) {
        abilities.pop();
    }

    for (Ability *ability: abilitySet) {
        delete ability;
    }
}

void AbilityManager::methodAbility(){
    if (!abilities.empty()){
        Ability* ability = abilities.front();
        abilities.pop();
        ability->useAbility();
    }else{
        throw AbilityError("Error: There is no abilities to use.");
    }
}

void AbilityManager::addRandomAbility(){
    int randomIndex = rand() % abilitySet.size();
    abilities.push(abilitySet[randomIndex]);
}