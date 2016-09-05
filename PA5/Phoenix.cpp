/*
 * Phoenix.cpp
 *
 *  Created on: 2015Äê11ÔÂ13ÈÕ
 *      Author: ThinkPad
 */
#include "Phoenix.h"

Phoenix::Phoenix(Game* game, int player, int position) :
		Animal(game, player, position) {
	hp = MAX_HP;
	atk_damage = DEFAULT_ATK_DAMAGE;
	name = "Phoenix";
	revive = true;
}

Phoenix::~Phoenix() {

}

void Phoenix::attack() {
	if (hp < 12) {
		hp = hp + 10;
		ac = 0.7;
	} else {
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
}
void Phoenix::takeDamage(int damage) {
	hp -= damage;
	if (hp <= 0) {
		if (revive) {
			revive = false;
			morale = 0;
			ac = 1.0;
			hp = MAX_HP;
		} else {
			die();
		}
	}
}
