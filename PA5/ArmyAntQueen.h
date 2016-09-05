/*
 * ArmyAntQueen.h
 *
 *  Created on: 2015��11��9��
 *      Author: ThinkPad
 */

#ifndef ARMYANTQUEEN_H_
#define ARMYANTQUEEN_H_
#include "Animal.h"

class ArmyAntQueen: public Animal {
public:
	ArmyAntQueen(Game* game, int player, int position);
	virtual ~ArmyAntQueen();

	virtual void attack();
	virtual void defend (Animal* opponent, int damage);

private:
	static const int MAX_HP = 15;
	static const int DEFAULT_ATK_DAMAGE = 0;
};




#endif /* ARMYANTQUEEN_H_ */
