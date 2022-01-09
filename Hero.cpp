#include "Hero.h"

Hero::Hero(sf::Vector2i initPos) {
	this->currHp = 100;
	this->maxHp = 100;
	this->level = 1;
	this->xpToNextLevel = 100;
	this->currXp = 0;
	this->position = initPos;
	this->lastMoved = sf::seconds(-1.01f);;
	setTexture();
}


sf::Texture& Hero::getTexture() {
	return this->texture;
}


void Hero::setTexture () {
	sf::Texture texture;
	if (!texture.loadFromFile("Resources/Hero.png")) {
		std::cout << "you fucked up" << std::endl;
	}
	this->texture = texture;
}

void Hero::move(sf::Vector2i dir) {
	sf::Time currTime = clock.getElapsedTime();
	if ((currTime - lastMoved).asSeconds() > 0.15) {
		lastMoved = currTime;
		this->position += dir;
	}

}

sf::Vector2i Hero::getPosition() {
	return this->position;
}
