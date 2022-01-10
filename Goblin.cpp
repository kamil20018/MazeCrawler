#include "Goblin.h"


Goblin::Goblin(sf::Vector2i initPos, std::shared_ptr<Floor> floor) : Enemy(initPos, floor) {
	setTexture();
}


void Goblin::takeTurn() {
	if (canSeeHero()) {
		moveTo(pathToHero[0]);
		std::cout << "goblin moved by vision" << std::endl;
	}
	else if (pathToHero.size() > 0) {
		moveTo(pathToHero[0]);
		pathToHero.erase(pathToHero.begin());
		std::cout << "goblin moved by memory" << std::endl;
	}
	std::cout << "goblin took turn" << std::endl;
}

void Goblin::setTexture() {
	sf::Texture texture;
	if (!texture.loadFromFile("Resources/Goblin.png")) {
		std::cout << "you fucked up" << std::endl;
	}
	this->texture = texture;

}