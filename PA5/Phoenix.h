/*
 * Phoenix.h
 *
 *  Created on: 2015��11��13��
 *      Author: ThinkPad
 */

#ifndef PHOENIX_H_
#define PHOENIX_H_
#include "Animal.h"

class Phoenix: public Animal {
public:
	Phoenix(Game* game, int player, int position);
	virtual ~Phoenix();

	virtual void attack();
	//override takeDamage
	virtual void takeDamage(int damage);
private:
	static const int MAX_HP = 25;
	static const int DEFAULT_ATK_DAMAGE = 5;
	// initialize the ability of revive
};




#endif /* PHOENIX_H_ */
