#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

class Hero {
	public:
		Hero(sf::Vector2i initPos);
		sf::Texture& getTexture();
		void move(sf::Vector2i dir);
		sf::Vector2i getPosition();

	private:
		int currHp;
		int maxHp;
		int level;
		int currXp;
		int xpToNextLevel;
		sf::Texture texture;
		sf::Vector2i position;
		void setTexture();
		sf::Clock clock;
		sf::Time lastMoved;
};