#include "Enemy.h"

Enemy::Enemy(sf::Vector2i position, std::shared_ptr<Floor> floor) {
	this->position = position;
	this->floor = floor;
	this->vision = 3;
	this->maxEnergy = 100;
	this->currEnergy = 100;
	this->speed = 2.3;
}

sf::Texture& Enemy::getTexture() {
	return this->texture;
}

sf::Vector2i Enemy::getPosition() {
	return this->position;
}

bool Enemy::canSeeHero() {
	std::vector<sf::Vector2i> path = floor->getPath(this->position, floor->getHeroPos());
	if (path.size() - 1 <= this->vision) {
		path.erase(path.begin());
		this->pathToHero = path;
		return true;
	}
	return false;
}

void Enemy::moveBy(sf::Vector2i moveBy) {
	float moveEnergy = 100.0 / this->speed;
	this->currEnergy -= moveEnergy;
	this->position += moveBy;
}

void Enemy::moveTo(sf::Vector2i moveTo) {
	float moveEnergy = 100.0 / this->speed;
	this->currEnergy -= moveEnergy;
	this->position = moveTo;
}

bool Enemy::canMove() {
	return this->currEnergy > 100.0 / this->speed;
}

bool Enemy::isDead() {
	return this->currentHp < 0;
}