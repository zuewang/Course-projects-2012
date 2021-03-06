/*
 * Cerberus.cpp
 *
 *  Created on: 2015��11��13��
 *      Author: ThinkPad
 */
#include "Cerberus.h"

Cerberus::Cerberus(Game* game, int player, int position) :
		Animal(game, player, position) {
	hp = MAX_HP;
	atk_damage = DEFAULT_ATK_DAMAGE;
	name = "Cerberus";

}

Cerberus::~Cerberus() {

}

void Cerberus::attack() {
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
}




