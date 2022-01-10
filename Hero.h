#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>


class Hero {
	public:
		Hero(sf::Vector2i initPos);
		sf::Texture& getTexture();
		bool move(sf::Vector2i dir);
		sf::Vector2i getPosition();
		void turnPassed();
		void setPosition(sf::Vector2i position);
		bool canMove();

	private:
		int currHp;
		int maxHp;

		int level;

		int currXp;
		int xpToNextLevel;

		float speed;
		float maxEnergy;
		float currEnergy;



		sf::Texture texture;
		sf::Vector2i position;
		void setTexture();
		sf::Clock clock;
		sf::Time lastMoved;
};