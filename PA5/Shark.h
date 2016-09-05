/*
 * Shark.h
 *
 *  Created on: 2015Äê11ÔÂ9ÈÕ
 *      Author: ThinkPad
 */

#ifndef SHARK_H_
#define SHARK_H_
#include "Animal.h"

class Shark: public Animal {
public:
	Shark(Game* game, int player, int position);
	virtual ~Shark();

	virtual void attack();
	// override defend
	virtual void defend(Animal* opponent, int damage);
private:
	static const int MAX_HP = 30;
	static const int DEFAULT_ATK_DAMAGE = 7;
	static const int REVENGE = 2;
};




#endif /* SHARK_H_ */
