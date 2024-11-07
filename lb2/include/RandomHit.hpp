#ifndef RANDOMHIT_HPP
#define RANDOMHIT_HPP

#include "Ability.hpp"

class RandomHit :public Ability {
private:
	GameField& field;
public:
	RandomHit(GameField& field);
	void useAbility()  override final;
};

#endif //RANDOMHIT_HPP