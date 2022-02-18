#include "Goblin.h"


Goblin::Goblin(sf::Vector2i initPos, std::shared_ptr<Floor> floor) : Enemy(initPos, floor) {
	this->meeleDmg = 10;
	this->meeleEnergy = 30;
	this->level = 1;

	this->maxEnergy = 100.0;
	this->currEnergy = 100.0;

	this->currentHp = 50;
	this->maxHp = 50;
	this->xpOnDeath = 20;
}


void Goblin::takeTurn() {
	bool canGetToHero = true;

	updatePathToHero();
	while (canMove() and pathToHero.size() >= 0) { //gets goblin as close as it can to hero
		if (pathToHero.size() == 0) {
			std::vector<sf::Vector2i> availableDirs;
			for (sf::Vector2i dir : dirs) {
				if (this->floor->canMoveTo(this->position, dir)) {
					availableDirs.push_back(dir);
				}
			}
			int dirCount = availableDirs.size();
			if (dirCount == 0) {
				break;
			}
			else {
				moveTo(this->position + availableDirs[rand() % dirCount]);
			}
		}
		else {
			if (not this->floor->canMoveTo(this->position, pathToHero[0] - this->position)) break;
			moveTo(pathToHero[0]);
			pathToHero.erase(pathToHero.begin());
		}
		updatePathToHero();
	}
	if (pathToHero.size() == 1 and pathToHero[0] == this->floor->getHeroPos()) { // attacks if is next to hero
		while (this->currEnergy > this->meeleEnergy) {
			std::cout << "hit the hero for" << this->meeleDmg << "dmg" << std::endl;
			this->attackListener->attackHeroAt(pathToHero[0], this->meeleDmg);
			this->currEnergy -= this->meeleEnergy;
		}
		std::cout << "goblin should attack now" << std::endl;
	}
	std::cout << "goblin took turn" << std::endl;
	this->currEnergy = maxEnergy;
}

bool Goblin::canPerformAction() {
	float moveEnergy = 100.0f / this->speed;
	return this->meeleEnergy < this->currEnergy or moveEnergy < this->currEnergy;
}


