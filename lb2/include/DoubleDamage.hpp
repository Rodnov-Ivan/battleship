#ifndef DOUBLEDAMAGE_HPP
#define DOUBLEDAMAGE_HPP

#include "Ability.hpp"

class DoubleDamage : public Ability{
private:
	GameField& field;
public:
	DoubleDamage(GameField& field);	
	void useAbility() override final;
};

#endif //DOUBLEDAMAGE_HPP
