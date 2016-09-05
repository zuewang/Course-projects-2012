/*
 * Hawk.cpp
 *
 *  Created on: 2015Äê11ÔÂ9ÈÕ
 *      Author: ThinkPad
 */
#include "Hawk.h"

Hawk::Hawk(Game* game, int player, int position) :
		Animal(game, player, position) {
	hp = MAX_HP;
	atk_damage = DEFAULT_ATK_DAMAGE;
	name = "Hawk";
	ac = AC;
	revenge = REVENGE;
}

Hawk::~Hawk() {

}

void Hawk::attack() {
	// the attack of the hawk is indefensible
	if (!enemies[pos]->isDead())
		enemies[pos]->takeDamage(morale + atk_damage);
	else {
		for (int i = 1; i < 5; i++) {
			if (pos - i >= 0 && !enemies[pos - i]->isDead()) {
				enemies[pos - i]->takeDamage(morale + atk_damage);
				break;
			} else if (pos + i < 5 && !enemies[pos + i]->isDead()) {
				enemies[pos + i]->takeDamage(morale + atk_damage);
				break;
			}
		}
	}
	// morale increases by 1 once hawk kills an enemy
	if (enemies[pos]->isDead()) {
		morale ++;
	}
}

void Hawk::defend(Animal* opponent, int damage) {
	takeDamage(ac * (opponent->getMorale() + damage));
	if (!is_dead) {
		opponent->takeDamage(revenge);
	}
	if (is_dead && if_morale == 'y') {
		opponent->moraleIncrement();
	}
}

