/**
 *  You SHOULD NOT modify this file
 */
#ifndef ANIMAL_H_
#define ANIMAL_H_
#include <string>

#include "Game.h"
class Game;

class Animal {
public:
	virtual ~Animal();

	virtual void attack() = 0;
	virtual void defend(Animal* opponent, int damage);

	virtual void takeDamage(int damage);
	void die();
	bool isDead() const;
	std::string getName() const;
	int getCurrentHP() const;
	//new added: modify the hp during special move if needed
	virtual void hpChange(int);
	//increase the morale by 1
	void moraleIncrement();
	//return morale (int)
	int getMorale() const;
	//whether the user wants to turn on morale system
	char if_morale;
protected:
	int hp;
	int atk_damage;
	bool is_dead;
	int pos;
	int revenge;
	bool revive;		//set revive as false as default in Animal.cpp
	double ac;			//set the defensive coefficient as 1.0 as default in Animal.cpp
	int morale;			//set the morale as 0 as default in Animal.cpp
	std::string name;
	Animal** allies;
	Animal** enemies;

	Animal(Game *game, int player, int position);

};

#endif /* ANIMAL_H_ */
