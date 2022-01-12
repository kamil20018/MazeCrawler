#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>
#include "EnemyManager.h"

class EnemyManager;

class Hero {
	public:
		Hero(sf::Vector2i initPos, std::shared_ptr<EnemyManager> enemyManager);
		sf::Texture& getTexture();
		bool move(sf::Vector2i dir);
		sf::Vector2i getPosition();
		void turnPassed();
		void setPosition(sf::Vector2i position);
		bool canMove();
		void meeleAttack(sf::Vector2i position);
		void addXp(float xp);
		void levelUp();

	private:
		int currHp;
		int maxHp;

		int level;

		int currXp;
		int xpToNextLevel;

		float speed;
		float maxEnergy;
		float currEnergy;

		float meeleDmg;
		float meeleAttackEnergy;
		sf::Texture texture;
		sf::Vector2i position;
		void setTexture();
		sf::Clock clock;
		sf::Time lastMoved;

		std::shared_ptr<EnemyManager> enemyManager;
};