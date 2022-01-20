#include "AttackListener.h"

AttackListener::AttackListener(std::shared_ptr<Hero> hero, std::shared_ptr<EnemyManager> enemyManager) {
	this->hero = hero;
	this->enemyManager = enemyManager;
}

void AttackListener::attackHeroAt(sf::Vector2i position, float damage) {
	this->hero->takeDamage(damage);
}

void AttackListener::attackEnemyAt(sf::Vector2i position, float damage) {
	this->enemyManager->damageEnemyAt(position, damage);
}