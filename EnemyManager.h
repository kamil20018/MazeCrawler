#pragma once


#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include "Enemy.h"

class Enemy;

class EnemyManager {
	public:
		void addEnemy(std::shared_ptr<Enemy> enemy);
		void takeTurn();
		void canSeeHero();
		
		std::vector<std::pair<sf::Vector2i, sf::Texture&>> getEnemyTextures();
		std::vector<sf::Vector2i> getEnemyPositions();
	private:
		std::vector<std::shared_ptr<Enemy>> enemyList;
		void removeDead();
};