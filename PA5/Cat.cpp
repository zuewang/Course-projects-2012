/*
 * Cat.cpp
 *
 *  Created on: 2015Äê11ÔÂ9ÈÕ
 *      Author: ThinkPad
 */
#include "Cat.h"

Cat::Cat(Game* game, int player, int position) :
		Animal(game, player, position) {
	hp = MAX_HP;
	atk_damage = DEFAULT_ATK_DAMAGE;
	name = "Cat";

}

Cat::~Cat() {

}

void Cat::attack() {
	double coef = 1.0;
	if (hp<13){
		coef = 1.5;
	}
	if (!enemies[pos]->isDead())
		enemies[pos]->defend(this, atk_damage*coef);
	else {
		for (int i = 1; i < 5; i++) {
			if (pos - i >= 0 && !enemies[pos - i]->isDead()) {
				enemies[pos - i]->defend(this, atk_damage*coef);
				break;
			} else if (pos + i < 5 && !enemies[pos + i]->isDead()) {
				enemies[pos + i]->defend(this, atk_damage*coef);
				break;
			}
		}
	}
}




