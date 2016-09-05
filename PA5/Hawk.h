/*
 * Hawk.h
 *
 *  Created on: 2015Äê11ÔÂ9ÈÕ
 *      Author: ThinkPad
 */

#ifndef HAWK_H_
#define HAWK_H_
#include "Animal.h"

class Hawk: public Animal {
public:
	Hawk(Game* game, int player, int position);
	virtual ~Hawk();

	virtual void attack();
	//override the defend function
	virtual void defend (Animal* opponent, int damage);
private:
	static const int MAX_HP = 25;
	static const int DEFAULT_ATK_DAMAGE = 5;
	static const double AC = 0.7;
	static const int REVENGE = 1;
};




#endif /* HAWK_H_ */
