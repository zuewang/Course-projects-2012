/*
 * ArmyAnt.cpp
 *
 *  Created on: 2015Äê11ÔÂ9ÈÕ
 *      Author: ThinkPad
 */
#include "ArmyAnt.h"

ArmyAnt::ArmyAnt(Game* game, int player, int position) :
		Animal(game, player, position) {
	hp = MAX_HP;
	atk_damage = DEFAULT_ATK_DAMAGE;
	name = "ArmyAnt";

}

ArmyAnt::~ArmyAnt() {

}

void ArmyAnt::attack() {
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

void ArmyAnt::hpChange(int change) {
	if (hp > 0) {
		hp += change;
	}
	// is_dead becomes true if hp <= 0
	if (hp <= 0) {
		is_dead = true;
	}
	//  do not "over heal" the ants
	if (hp > MAX_HP) {
		hp = MAX_HP;
	}
}

