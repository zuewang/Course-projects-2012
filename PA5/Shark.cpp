/*
 * Shark.cpp
 *
 *  Created on: 2015Äê11ÔÂ9ÈÕ
 *      Author: ThinkPad
 */
#include "Shark.h"

Shark::Shark(Game* game, int player, int position) :
		Animal(game, player, position) {
	hp = MAX_HP;
	atk_damage = DEFAULT_ATK_DAMAGE;
	name = "Shark";
	revenge = REVENGE;
}

Shark::~Shark() {

}

void Shark::attack() {
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
	// hurt itself by 1 hp
	hpChange(-1);
}

void Shark::defend(Animal *opponent, int damage) {
	takeDamage(opponent->getMorale() + damage);
	if (!is_dead) {
		opponent->takeDamage(revenge);
	}
	if (is_dead && if_morale == 'y') {
		opponent->moraleIncrement();
	}
}

