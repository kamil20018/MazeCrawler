#include "EnemyManager.h"

void EnemyManager::addEnemy(std::shared_ptr<Enemy> enemy) {
	this->enemyList.push_back(enemy);
}

void EnemyManager::removeDead() {
	std::vector<int> deadEnemies;
	for (int i = this->enemyList.size() - 1; i >= 0; i--) {
		if (this->enemyList[i]->isDead()) {
			deadEnemies.push_back(i);
		}
	}
	for (int deadEnemyIndex : deadEnemies) {
		this->enemyList.erase(this->enemyList.begin() + deadEnemyIndex);
	}
}

std::tuple<float> EnemyManager::getLootFromDead() { //it returns a tuple, cause enemies will drop items etc later on
	float totalXpGain = 0;
	for (std::shared_ptr enemy : this->enemyList) {
		if (enemy->isDead()) {
			totalXpGain += enemy->getXpOnDeath();
		}
	}
	std::tuple<float> output = std::make_tuple(totalXpGain);
	return output;
}

void EnemyManager::takeTurn() {
	for (std::shared_ptr<Enemy> enemy : this->enemyList) {
		enemy->takeTurn();
	}
}

void EnemyManager::updatePathToHero() {
	for (std::shared_ptr<Enemy> enemy : this->enemyList) {
		enemy->updatePathToHero();
	}
}


std::vector<sf::Vector2i> EnemyManager::getEnemyPositions() {
	std::vector<sf::Vector2i> enemyPositions;
	for (std::shared_ptr<Enemy> enemy : this->enemyList) {
		enemyPositions.push_back(enemy->getPosition());
	}
	return enemyPositions;
}

void EnemyManager::damageEnemyAt(sf::Vector2i position, float damage) {
	for (std::shared_ptr<Enemy> enemy : this->enemyList) {
		if (enemy->getPosition() == position) {
			enemy->takeDamage(damage);
		}
	}
}

bool EnemyManager::isEnemyAt(sf::Vector2i position) {
	return utils::isInVector(position, getEnemyPositions());
}
std::vector<std::shared_ptr<Enemy>> EnemyManager::getEnemyList() {
	return this->enemyList;
}