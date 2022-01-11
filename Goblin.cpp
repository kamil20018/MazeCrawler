#include "Goblin.h"


Goblin::Goblin(sf::Vector2i initPos, std::shared_ptr<Floor> floor) : Enemy(initPos, floor) {
	setTexture();
	meeleDmg = 10;
	currentHp = 50;
	maxHp = 50;
}


void Goblin::takeTurn() {
	if (canSeeHero()) {
		while (canMove() and pathToHero.size() > 1) {
			if (not this->floor->canMoveTo(this->position, pathToHero[0] - this->position)) break;
			moveTo(pathToHero[0]);
			pathToHero.erase(pathToHero.begin());
			std::cout << "goblin moved by vision" << std::endl;
		}
	}
	else if (pathToHero.size() > 0) {
		while (canMove() and pathToHero.size() > 1) {
			if (not this->floor->canMoveTo(this->position, pathToHero[0] - this->position)) break;
			moveTo(pathToHero[0]);
			pathToHero.erase(pathToHero.begin());
			std::cout << "goblin moved by memory" << std::endl;
		}
	}
	std::cout << "goblin took turn" << std::endl;

	this->currEnergy = maxEnergy;
}

void Goblin::setTexture() {
	sf::Texture texture;
	if (!texture.loadFromFile("Resources/Goblin.png")) {
		std::cout << "you fucked up" << std::endl;
	}
	this->texture = texture;

}