/*
 * Bat.cpp
 *
 *  Created on: 2015��11��9��
 *      Author: ThinkPad
 */
#include "Bat.h"
Bat::Bat(Game* game, int player, int position) :
		Animal(game, player, position) {
	hp = MAX_HP;
	atk_damage = DEFAULT_ATK_DAMAGE;
	name = "Bat";
	ac = 0.8;
}

Bat::~Bat() {

}

void Bat::attack() {
	if (!enemies[pos]->isDead())
		enemies[pos]->defend(this, atk_damage);
	else {
		for (int i = 1; i < 5; i++) {
			if (pos - i >= 0 && !enemies[pos - i]->isDead()) {
				enemies[pos - i]->defend(this, atk_damage);
				break;
			} else if (pos + i < 5 && !enemies[pos + i]->isDead()) {
				enemies[pos + i]->defend(this, atk_damage);
				break;
			}
		}
	}
	// heal itself by 1 hp
	hpChange(1);
	// do not "over heal" itself
	if (hp > MAX_HP) {
		hp = MAX_HP;
	}
}




