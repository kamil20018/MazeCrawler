#pragma once


#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include "Enemy.h"
#include "AttackListener.h"

class Enemy;
class AttackListener;

class EnemyManager {
	public:
		void addEnemy(std::shared_ptr<Enemy> enemy);
		void takeTurn();
		void updatePathToHero();
		void damageEnemyAt(sf::Vector2i position, float damage);
		bool isEnemyAt(sf::Vector2i position);
		void removeDead();
		void setAttackListener(std::shared_ptr<AttackListener> listener);
		void setEnemyList(std::vector<std::shared_ptr<Enemy>> enemyList);
		std::tuple<float> getLootFromDead();
		std::vector<sf::Vector2i> getEnemyPositions();
		std::vector<std::shared_ptr<Enemy>> getEnemyList();
	private:
		std::vector<std::shared_ptr<Enemy>> enemyList;

};