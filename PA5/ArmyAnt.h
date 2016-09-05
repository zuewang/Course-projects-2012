/*
 * ArmyAnt.h
 *
 *  Created on: 2015��11��9��
 *      Author: ThinkPad
 */

#ifndef ARMYANT_H_
#define ARMYANT_H_
#include "Animal.h"

class ArmyAnt: public Animal {
public:
	ArmyAnt(Game* game, int player, int position);
	virtual ~ArmyAnt();

	virtual void attack();
	//override hpChange
	virtual void hpChange(int);

private:
	static const int MAX_HP = 15;
	static const int DEFAULT_ATK_DAMAGE = 1;
};




#endif /* ARMYANT_H_ */
