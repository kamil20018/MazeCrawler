#include "Hero.h"

Hero::Hero(sf::Vector2i initPos, std::shared_ptr<EnemyManager> enemyManager, const sf::Texture& texture) {
	this->texture = texture;
	this->currHp = 100.0;
	this->maxHp = 100.0;
	this->level = 1;
	this->meeleDmg = 10.0;
	this->meeleAttackEnergy = 20.0;
	this->xpToNextLevel = 100.0;
	this->currXp = 0;
	this->position = initPos;
	this->maxEnergy = 100.0;
	this->currEnergy = 100.0;
	this->speed = 3.3f;
	this->lastMoved = sf::seconds(-1.01f);;
	this->enemyManager = enemyManager;
	this->vision = 3;
}

sf::Texture& Hero::getTexture() {
	return this->texture;
}

bool Hero::move(sf::Vector2i dir) {
	sf::Time currTime = clock.getElapsedTime();
	float moveEnergy = 100.0f / this->speed;
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

int Hero::getVision() {
	return this->vision;
}

void Hero::turnPassed() {
	this->currEnergy = this->maxEnergy;
}

void Hero::setPosition(sf::Vector2i position) {
	this->position = position;
}

bool Hero::canMove() {
	float moveEnergy = 100.0f / this->speed;
	return this->currEnergy > moveEnergy;
}

bool Hero::canTakeAction() { // actions like spells / attacks will be added later
	float moveEnergy = 100.0f / this->speed;
	return this->currEnergy > moveEnergy or this->currEnergy > this->meeleAttackEnergy;
}

void Hero::addXp(float xp) {
	this->currXp += xp;
	if (xp > 0.0000001) {
		std::cout << "got xp" << std::endl;
	}
	
	if (xp > this->xpToNextLevel) levelUp();
}

void Hero::levelUp() {

}

void Hero::meeleAttack(sf::Vector2i position) {
	if (this->currEnergy > this->meeleAttackEnergy and this->enemyManager->isEnemyAt(position)) {
		this->enemyManager->damageEnemyAt(position, this->meeleDmg);
		this->currEnergy -= this->meeleAttackEnergy;
		std::tuple<float> loot = this->enemyManager->getLootFromDead();
		addXp(std::get<0>(loot));
		this->enemyManager->removeDead();
	}
}

HeroData* Hero::getHeroData() {
	return &this->heroData;
}