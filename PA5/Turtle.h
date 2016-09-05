/*
 * Turtle.h
 *
 *  Created on: 2015��11��9��
 *      Author: ThinkPad
 */

#ifndef TURTLE_H_
#define TURTLE_H_
#include "Animal.h"

class Turtle: public Animal {
public:
	Turtle(Game* game, int player, int position);
	virtual ~Turtle();

	virtual void attack();

private:
	static const int MAX_HP = 35;
	static const int DEFAULT_ATK_DAMAGE = 2;
};




#endif /* TURTLE_H_ */
