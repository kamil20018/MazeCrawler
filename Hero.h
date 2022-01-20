#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>
#include "EnemyManager.h"
#include "Constants.h"

class AttackListener;

class Hero {
	public:
		Hero(sf::Vector2i initPos, const sf::Texture& texture);
		sf::Texture& getTexture();
		bool move(sf::Vector2i dir);
		sf::Vector2i getPosition();
		void turnPassed();
		void setPosition(sf::Vector2i position);
		int getVision();
		bool canMove();
		bool canTakeAction();
		void meeleAttack(sf::Vector2i position);
		void addXp(float xp);
		void levelUp();
		void takeDamage(float damage);
		void setAttackListener(std::shared_ptr<AttackListener> listener);
		void getLoot(std::tuple<float> loot);

		HeroData* getHeroData();

	protected:
		float currHp;
		float maxHp;

		int level;
		int vision;


		float currXp;
		float xpToNextLevel;

		float speed;

		float currEnergy;
		float maxEnergy;


		float meeleDmg;
		float meeleAttackEnergy;
		sf::Texture texture;
		sf::Vector2i position;
		sf::Clock clock;
		sf::Time lastMoved;
		HeroData heroData = { this->level, this->currHp, this->maxHp, this->currXp, this->xpToNextLevel, this->currEnergy, this->maxEnergy };
		std::shared_ptr<AttackListener> attackListener;
};