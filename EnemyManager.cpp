#include "EnemyManager.h"

EnemyManager::EnemyManager() {

}

void EnemyManager::addEnemy(std::shared_ptr<Enemy> enemy) {
	this->enemyList.push_back(enemy);
}

void EnemyManager::setEnemyList(std::vector<std::shared_ptr<Enemy>> enemyList) {
	this->enemyList = enemyList;
}

void EnemyManager::removeDead() {
	std::vector<int> deadEnemies;
	for (int i = (int)this->enemyList.size() - 1; i >= 0; i--) {
		if (this->enemyList[i]->isDead()) {
			deadEnemies.push_back(i);
		}
	}
	for (int deadEnemyIndex : deadEnemies) {
		this->enemyList.erase(this->enemyList.begin() + deadEnemyIndex);
	}
}

EnemyLoot EnemyManager::getLootFromDead() { //it returns a tuple, cause enemies will drop items etc later on
	float totalXpGain = 0;
	std::vector<int> enemyLevels;
	for (std::shared_ptr enemy : this->enemyList) {
		if (enemy->isDead()) {
			enemyLevels.push_back(enemy->getLevel());
			totalXpGain += enemy->getXpOnDeath();
		}
	}
	std::vector<std::shared_ptr<Item>> items = this->itemGenerator.generateItems(enemyLevels);
	return EnemyLoot{totalXpGain, items};
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

void EnemyManager::setAttackListener(std::shared_ptr<AttackListener> listener) {
	for (std::shared_ptr<Enemy> enemy : this->enemyList) {
		enemy->addAttackListener(listener);
	}
}