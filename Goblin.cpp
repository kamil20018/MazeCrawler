#include "Goblin.h"


Goblin::Goblin(sf::Vector2i initPos, std::shared_ptr<Floor> floor) : Enemy(initPos, floor) {
	setTexture();
}

void Goblin::move(sf::Vector2i dir) {
	this->position += dir;
}

void Goblin::setTexture() {
	sf::Texture texture;
	if (!texture.loadFromFile("Resources/Goblin.png")) {
		std::cout << "you fucked up" << std::endl;
	}
	this->texture = texture;

}