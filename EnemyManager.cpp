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

void EnemyManager::takeTurn() {
	for (std::shared_ptr<Enemy> enemy : this->enemyList) {
		enemy->takeTurn();
	}
}

void EnemyManager::canSeeHero() {
	for (std::shared_ptr<Enemy> enemy : this->enemyList) {
		enemy->canSeeHero();
	}
}

std::vector<std::pair<sf::Vector2i, sf::Texture&>> EnemyManager::getEnemyTextures() {
	std::vector<std::pair<sf::Vector2i, sf::Texture&>> enemyTextures;
	for (std::shared_ptr<Enemy> enemy : this->enemyList) {
		std::pair<sf::Vector2i, sf::Texture&> pair(enemy->getPosition(), enemy->getTexture());
		enemyTextures.push_back(pair);
	}
	return enemyTextures;
}
std::vector<sf::Vector2i> EnemyManager::getEnemyPositions() {
	std::vector<sf::Vector2i> enemyPositions;
	for (std::shared_ptr<Enemy> enemy : this->enemyList) {
		enemyPositions.push_back(enemy->getPosition());
	}
	return enemyPositions;
}