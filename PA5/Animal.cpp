/**
 *  You SHOULD NOT modify this file
 */
#include "Animal.h"

Animal::Animal(Game* game, int player, int position) {
	allies = game->animals[player];
	enemies = game->animals[!player];
	pos = position;
	is_dead = false;
	//new-added variables
	revenge = 0;
	ac = 1.0;
	morale = 0;
	revive = false;
}

Animal::~Animal() {

}

void Animal::defend(Animal* opponent, int damage) {
	takeDamage(ac * (opponent->morale + damage));
	if (is_dead && if_morale == 'y') {
		opponent->morale++;
	}
}

void Animal::die() {
	is_dead = true;
}

void Animal::takeDamage(int damage) {
	hp -= damage;
	if (hp <= 0) {
		die();
	}
}

bool Animal::isDead() const {
	return is_dead;
}

std::string Animal::getName() const {
	return name;
}

int Animal::getCurrentHP() const {
	return hp;
}

void Animal::hpChange(int change) {
	// if the animal is alive, the hpChange can take effect (dead ants or bats can not be healed)
	if (hp > 0) {
		hp += change;
	}
	// is_dead becomes true if hp <= 0
	if (hp <= 0) {
		is_dead = true;
	}
}

int Animal::getMorale() const {
	return morale;
}
void Animal::moraleIncrement() {
	morale++;
}
