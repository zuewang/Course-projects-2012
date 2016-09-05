/*
 * Dragon.cpp
 *
 *  Created on: 2015Äê11ÔÂ9ÈÕ
 *      Author: ThinkPad
 */
#include "Dragon.h"

Dragon::Dragon(Game* game, int player, int position) :
		Animal(game, player, position) {
	hp = MAX_HP;
	atk_damage = DEFAULT_ATK_DAMAGE;
	name = "Dragon";
	ac = 0.8;
}

Dragon::~Dragon() {

}

void Dragon::attack() {
	for (int i = pos - 1; i <= pos + 1; i++) {
		if (i >= 0 && i <= 4 && !enemies[i]->isDead())
			enemies[i]->defend(this, atk_damage);
	}
}

