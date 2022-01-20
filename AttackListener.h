#pragma once

#include "Enemy.h"
#include "Hero.h"
#include "EnemyManager.h"
#include <SFML/Graphics.hpp>
class Hero;
class EnemyManager;
class AttackListener {
	public:
		AttackListener(std::shared_ptr<Hero> hero, std::shared_ptr<EnemyManager> enemyManager);
		void attackHeroAt(sf::Vector2i position, float damage);
		void attackEnemyAt(sf::Vector2i position, float damage);
	private:
		std::shared_ptr<EnemyManager> enemyManager;
		std::shared_ptr<Hero> hero;
};