#include <iostream>
#include <fstream>
#include <vector>

#include "Game.h"
#include "Dog.h"
#include "ArmyAnt.h"
#include "ArmyAntQueen.h"
#include "Bat.h"
#include "Cat.h"
#include "Dragon.h"
#include "Hawk.h"
#include "Shark.h"
#include "Turtle.h"
#include "Phoenix.h"
#include "Cerberus.h"
/*
 * Remember to include the header file of the animal classes here
 */

using namespace std;

Game::Game(std::string file) {
	load(file);
}

Game::~Game() {
	for (int i = 0; i < 10; i++)
		delete animals[i / 5][i % 5];
}

/**
 * You should instantiate the animal objects here
 * Please refer to the example of "Dog" 
 */
void Game::load(std::string file) {
	ifstream in(file.c_str());
	int c = 0;
	int id;
	while (in >> id) {
		switch (id) {
		case DOG:
			animals[c / 5][c % 5] = new Dog(this, c / 5, c % 5);
			break;
		case CAT:
			animals[c / 5][c % 5] = new Cat(this, c / 5, c % 5);
			break;
		case HAWK:
			animals[c / 5][c % 5] = new Hawk(this, c / 5, c % 5);
			break;
		case BAT:
			animals[c / 5][c % 5] = new Bat(this, c / 5, c % 5);
			break;
		case TURTLE:
			animals[c / 5][c % 5] = new Turtle(this, c / 5, c % 5);
			break;
		case SHARK:
			animals[c / 5][c % 5] = new Shark(this, c / 5, c % 5);
			break;
		case ARMY_ANT:
			animals[c / 5][c % 5] = new ArmyAnt(this, c / 5, c % 5);
			break;
		case ARMY_ANT_QUEEN:
			animals[c / 5][c % 5] = new ArmyAntQueen(this, c / 5, c % 5);
			break;
		case DRAGON:
			animals[c / 5][c % 5] = new Dragon(this, c / 5, c % 5);
			break;
		case PHOENIX:
			animals[c / 5][c % 5] = new Phoenix(this, c / 5, c % 5);
			break;
		case CERBERUS:
			animals[c / 5][c % 5] = new Cerberus(this, c / 5, c % 5);
			break;
		}

		c++;
	}

}

/**
 * Do NOT modify this function
 */
bool Game::isEnd() {
	int deadCount1 = 0;
	int deadCount2 = 0;
	for (int i = 0; i < 5; i++) {
		deadCount1 += animals[P1][i]->isDead();
		deadCount2 += animals[P2][i]->isDead();
	}

	if (deadCount1 == 5 && deadCount2 == 5) {
		cout << "Draws!" << endl;
	} else if (deadCount1 == 5) {
		cout << "Player " << P2 + 1 << " Wins!" << endl;
	} else if (deadCount2 == 5) {
		cout << "Player " << P1 + 1 << " Wins!" << endl;
	} else {
		return false;
	}
	return true;

}
//special move: harass
void Game::harass(int player) {
	int damage = 0;
	for (int i = 0; i < 5; i++) {
		if (animals[player][i]->getName() == "Hawk"
				&& !animals[player][i]->isDead()) {
			damage++;
		}
		if (animals[player][i]->getName() == "Bat"
				&& !animals[player][i]->isDead()) {
			damage++;
			//avoid "over healing " the bat
			if (animals[player][i]->getCurrentHP() < 20){
				animals[player][i]->hpChange(1);
			}

		}
		if ((animals[player][i]->getName() == "Dragon"
				|| animals[player][i]->getName() == "Phoenix")
				&& !animals[player][i]->isDead()) {
			damage = damage + 2;
		}
	}
	for (int i = 0; i < 5; i++) {
		animals[1 - player][i]->takeDamage(damage);
	}
}
//special move: summonTsunami
void Game::summonTsunami(int player) {
	int damage = 0;
	for (int i = 0; i < 5; i++) {
		if (animals[player][i]->getName() == "Turtle"
				&& !animals[player][i]->isDead()) {
			damage++;
		}
		if (animals[player][i]->getName() == "Shark"
				&& !animals[player][i]->isDead()) {
			damage = damage + 2;
			animals[player][i]->hpChange(-2);
		}
	}
	for (int i = 0; i < 5; i++) {
		animals[1 - player][i]->takeDamage(damage);
	}
}
//special move: marchAndConquer
void Game::marchAndConquer(int player) {
	int damage = 0, heal = 0;
	// calculate the heal
	for (int i = 0; i < 5; i++) {
		if (animals[player][i]->getName() == "ArmyAntQueen"
				&& !animals[player][i]->isDead()) {
			heal = heal + 2;
		}
	}
	// heal and damage
	for (int i = 0; i < 5; i++) {
		if (animals[player][i]->getName() == "ArmyAnt"
				&& !animals[player][i]->isDead()) {
			damage = damage + 3;
			animals[player][i]->hpChange(heal);
		}
	}
	for (int i = 0; i < 5; i++) {
		animals[1 - player][i]->takeDamage(damage);
	}
}
// special move: weatherStorm
void Game::weatherStorm(int player, int num) {
	for (int i = 0; i < 5; i++) {
		animals[1 - player][i]->takeDamage(num * 3);
	}
}
//special move: dogAttack
void Game::dogAttack(int player, int cerberus, int dog) {
	for (int i = 0; i < 5; i++) {
		animals[1 - player][i]->takeDamage(cerberus * 2 + dog);
	}
}
void Game::start() {
	Player currentPlayer = P1;
	int turnCount = 1;
	char if_morale_system;
	//ask the user whether or not turn on the morale system
	cout << "Do you want to turn on morale system? ('y' for yes and other characters for no)" << endl;
	cin >> if_morale_system;
	//input to Animal
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 5; j++) {
			animals[i][j]->if_morale = if_morale_system;
		}
	}
	//ask the user whether or not turn on the dog-aggregation system
	cout << "Do you want to turn on dog-aggregation system? ('y' for yes and other characters for no)" << endl;
	cin >> if_combine_dog;
	while (!isEnd()) {
		//normal attack
		for (int i = 0; i < 5; i++) {
			if (!animals[currentPlayer][i]->isDead()) {
				animals[currentPlayer][i]->attack();
			}
		}

		int num_swim_animal = 0, num_fly_animal = 0, num_army_ant = 0,
				num_legendary_animal = 0, num_cerberus = 0, num_ally_dog = 0;
		vector<int> index_dog;
		index_dog.clear();
		for (int i = 0; i < 5; i++) {
			if ((animals[currentPlayer][i]->getName() == "Hawk"
					|| animals[currentPlayer][i]->getName() == "Bat"
					|| animals[currentPlayer][i]->getName() == "Dragon"
					|| animals[currentPlayer][i]->getName() == "Phoenix")
					&& (!animals[currentPlayer][i]->isDead())) {
				num_fly_animal++;
			}
			if ((animals[currentPlayer][i]->getName() == "Turtle"
					|| animals[currentPlayer][i]->getName() == "Shark")
					&& (!animals[currentPlayer][i]->isDead())) {
				num_swim_animal++;
			}
			if ((animals[currentPlayer][i]->getName() == "ArmyAnt"
					|| animals[currentPlayer][i]->getName() == "ArmyAntQueen")
					&& (!animals[currentPlayer][i]->isDead())) {
				num_army_ant++;
			}
			if ((animals[currentPlayer][i]->getName() == "Dragon"
					|| animals[currentPlayer][i]->getName() == "Phoenix"
					|| animals[currentPlayer][i]->getName() == "Cerberus")
					&& (!animals[currentPlayer][i]->isDead())) {
				num_legendary_animal++;
			}
			if (animals[currentPlayer][i]->getName() == "Cerberus"
					&& (!animals[currentPlayer][i]->isDead())) {
				num_cerberus++;
			}
			if (animals[currentPlayer][i]->getName() == "Dog"
					&& (!animals[currentPlayer][i]->isDead())) {
				num_ally_dog++;
				index_dog.push_back(i);
			}
		}
		if (num_ally_dog >= 3 && if_combine_dog == 'y') {
			cout	<< "Which 3 dogs do you want to combine and produce a cerberus for Player"
					<< currentPlayer + 1 << "?" << endl;
			for (unsigned int i = 0; i < index_dog.size(); i++) {
				cout << index_dog[i] << ", ";
			}
			cout << endl << "or enter other numbers to stop aggregating dogs:" << endl;
			// store the inputs of the user
			int dog_1, dog_2, dog_3, num_correct_input = 0;
			cin >> dog_1 >> dog_2 >> dog_3;
			// check whether the inputs are correct
			for (unsigned int i = 0; i < index_dog.size(); i++) {
				if (index_dog[i] == dog_1 || index_dog[i] == dog_2 || index_dog[i] == dog_3) {
					num_correct_input++;
				}
			}
			if (num_correct_input == 3) {
				// kill 2 dogs and produce a cerberus
				animals[currentPlayer][dog_1]->takeDamage(100);
				animals[currentPlayer][dog_3]->takeDamage(100);
				animals[currentPlayer][dog_2] = new Cerberus(this, currentPlayer, dog_2);
				num_ally_dog = num_ally_dog - 3;
				num_cerberus++;
				num_legendary_animal++;
			}
		}

		/**
		 * To-Do 2: Codes for Special moves (if any) should be written here
		 * Hint: You should use dynamic binding, you may add data members/ functions in the Game class to help you implement this part
		 */

		if (num_fly_animal >= 3) {
			harass(currentPlayer);
		}
		if (num_swim_animal >= 3) {
			summonTsunami(currentPlayer);
		}
		if (num_army_ant == 5) {
			marchAndConquer(currentPlayer);
		}
		if (num_legendary_animal >= 3) {
			weatherStorm(currentPlayer, num_legendary_animal);
		}
		if (num_ally_dog && num_cerberus) {
			dogAttack(currentPlayer, num_cerberus, num_ally_dog);
		}

		//Output turn info
		cout << "Turn " << turnCount++ << " Player " << currentPlayer + 1 << " attacks:" << endl;
		cout << "Player 1" << endl;
		for (int i = 0; i < 5; i++) {
			if (!animals[P1][i]->isDead())
				cout << animals[P1][i]->getName() << ":"
						<< animals[P1][i]->getCurrentHP() << " ";
			else
				cout << animals[P1][i]->getName() << ":" << "DEAD" << " ";
		}
		cout << endl;
		cout << "Player 2" << endl;
		for (int i = 0; i < 5; i++) {
			if (!animals[P2][i]->isDead())
				cout << animals[P2][i]->getName() << ":"
						<< animals[P2][i]->getCurrentHP() << " ";
			else
				cout << animals[P2][i]->getName() << ":" << "DEAD" << " ";
		}
		cout << endl;

		//Switch player turn
		if (currentPlayer == P1)
			currentPlayer = P2;
		else
			currentPlayer = P1;
	}
}
