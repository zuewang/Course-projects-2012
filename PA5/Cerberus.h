/*
 * Cerberus.h
 *
 *  Created on: 2015Äê11ÔÂ13ÈÕ
 *      Author: ThinkPad
 */

#ifndef CERBERUS_H_
#define CERBERUS_H_
#include "Animal.h"

class Cerberus: public Animal {
public:
	Cerberus(Game* game, int player, int position);
	virtual ~Cerberus();

	virtual void attack();

private:
	static const int MAX_HP = 35;
	static const int DEFAULT_ATK_DAMAGE = 6;
};




#endif /* CERBERUS_H_ */
