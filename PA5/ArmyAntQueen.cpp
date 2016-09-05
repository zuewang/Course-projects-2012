/*
 * ArmyAntQueen.cpp
 *
 *  Created on: 2015Äê11ÔÂ9ÈÕ
 *      Author: ThinkPad
 */
#include "ArmyAntQueen.h"

ArmyAntQueen::ArmyAntQueen(Game* game, int player, int position) :
		Animal(game, player, position) {
	hp = MAX_HP;
	atk_damage = DEFAULT_ATK_DAMAGE;
	name = "ArmyAntQueen";

}

ArmyAntQueen::~ArmyAntQueen() {

}

void ArmyAntQueen::attack() {
	// no need to implement this because it does not attack
}

void ArmyAntQueen::defend(Animal* opponent, int damage) {
	takeDamage(opponent->getMorale() + damage);
	//revenge if not dead
	if (!is_dead) {
		int num_ant = 0;
		for (int i = 0; i < 5; i++) {
			if (allies[i]->getName() == "ArmyAnt" && !allies[i]->isDead()) {
				num_ant++;
			}
		}
		opponent->takeDamage(num_ant * 2);
	}
	if (is_dead && if_morale == 'y') {
		opponent->moraleIncrement();
	}
}

