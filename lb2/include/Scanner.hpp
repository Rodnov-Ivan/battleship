#ifndef SCANNER_HPP
#define SCANNER_HPP

#include "Ability.hpp"
#include "AbilityError.hpp"

class Scanner : public Ability {
private:
	GameField& field;
public:
	Scanner(GameField& field);
	void useAbility() override final;
};

#endif //SCANNER_HPP
