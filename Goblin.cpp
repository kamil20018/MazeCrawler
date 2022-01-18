#include "Goblin.h"


Goblin::Goblin(sf::Vector2i initPos, std::shared_ptr<Floor> floor) : Enemy(initPos, floor) {
	this->meeleDmg = 10;
	this->currentHp = 50;
	this->maxHp = 50;
	this->xpOnDeath = 20;
}


void Goblin::takeTurn() {
	updatePathToHero();
	while (canMove() and pathToHero.size() > 1) { //basic ai, to be expanded later
		if (not this->floor->canMoveTo(this->position, pathToHero[0] - this->position)) break;
		moveTo(pathToHero[0]);
		pathToHero.erase(pathToHero.begin());
		updatePathToHero();
	}
	updatePathToHero();
	std::cout << "goblin took turn" << std::endl;
	this->currEnergy = maxEnergy;
}



