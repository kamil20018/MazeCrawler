#include "Hero.h"

Hero::Hero(sf::Vector2i initPos) {
	this->currHp = 100;
	this->maxHp = 100;
	this->level = 1;
	this->xpToNextLevel = 100;
	this->currXp = 0;
	this->position = initPos;
	this->maxEnergy = 100;
	this->currEnergy = 100;
	this->speed = 3.3;
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

bool Hero::move(sf::Vector2i dir) {
	sf::Time currTime = clock.getElapsedTime();
	float moveEnergy = 100.0 / this->speed;
	if ((currTime - lastMoved).asSeconds() > 0.15 and moveEnergy < this->currEnergy) {
		this->currEnergy -= moveEnergy;
		lastMoved = currTime;
		this->position += dir;
		std::cout << "move energy: " << moveEnergy << std::endl;
		std::cout << "energy after move: " << this->currEnergy << std::endl;
		std::cout << std::endl;
		return true;
	}
	return false;
}

sf::Vector2i Hero::getPosition() {
	return this->position;
}

void Hero::turnPassed() {
	this->currEnergy = this->maxEnergy;
}

void Hero::setPosition(sf::Vector2i position) {
	this->position = position;
}

bool Hero::canMove() {
	float moveEnergy = 100.0 / this->speed;
	return this->currEnergy > moveEnergy;
}