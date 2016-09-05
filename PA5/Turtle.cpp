/*
 * Turtle.cpp
 *
 *  Created on: 2015��11��9��
 *      Author: ThinkPad
 */
#include "Turtle.h"

Turtle::Turtle(Game* game, int player, int position) :
		Animal(game, player, position) {
	hp = MAX_HP;
	atk_damage = DEFAULT_ATK_DAMAGE;
	name = "Turtle";
	ac = 0.5;
}

Turtle::~Turtle() {

}

void Turtle::attack() {
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




