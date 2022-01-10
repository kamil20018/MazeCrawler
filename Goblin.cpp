#include "Goblin.h"


Goblin::Goblin(sf::Vector2i initPos, std::shared_ptr<Floor> floor) : Enemy(initPos, floor) {
	setTexture();
}


void Goblin::takeTurn() {
	if (canSeeHero()) {
		sf::Vector2i moveBy = this->pathToHero[0] - this->position;
		move(moveBy);
		std::cout << "took turn" << std::endl;
	}

}

void Goblin::setTexture() {
	sf::Texture texture;
	if (!texture.loadFromFile("Resources/Goblin.png")) {
		std::cout << "you fucked up" << std::endl;
	}
	this->texture = texture;

}