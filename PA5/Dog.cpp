#include "Dog.h"

Dog::Dog(Game* game, int player, int position) :
		Animal(game, player, position) {
	hp = MAX_HP;
	atk_damage = DEFAULT_ATK_DAMAGE;
	name = "Dog";

}

Dog::~Dog() {

}

void Dog::attack() {
	// do not attack if the dog is "threatend" by Cerberus
	if ((enemies[pos]->getName() != "Cerberus" || enemies[pos]->isDead())
			&& (pos + 1 >= 5 || enemies[pos + 1]->getName() != "Cerberus"
					|| enemies[pos + 1]->isDead())
			&& (pos - 1 < 0 || enemies[pos - 1]->getName() != "Cerberus"
					|| enemies[pos - 1]->isDead())) {

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
