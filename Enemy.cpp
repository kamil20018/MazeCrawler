#include "Enemy.h"

Enemy::Enemy(sf::Vector2i position, std::shared_ptr<Floor> floor) {
	this->position = position;
	this->floor = floor;
}

sf::Texture& Enemy::getTexture() {
	return this->texture;
}

sf::Vector2i Enemy::getPosition() {
	return this->position;
}

bool Enemy::canSeeHero() { //write this later!!!!!!!!!!!!!!!!!!!!!

	return true;
}