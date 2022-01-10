#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Floor.h"

class Enemy {
	public:
		virtual void takeTurn() = 0;
		Enemy(sf::Vector2i position, std::shared_ptr<Floor> floor);
		sf::Texture& getTexture();
		sf::Vector2i getPosition();
		bool canSeeHero();
		
	protected:
		sf::Texture texture;
		sf::Vector2i position;
		std::shared_ptr<Floor> floor;
		std::vector<sf::Vector2i> pathToHero;
		int vision;
		void move(sf::Vector2i moveBy);
	private:

};