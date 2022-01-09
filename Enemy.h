#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Floor.h"

class Enemy {
	public:
		virtual void move(sf::Vector2i dir) = 0;
		Enemy(sf::Vector2i position, std::shared_ptr<Floor> floor);
		sf::Texture& getTexture();
		sf::Vector2i getPosition();
	protected:
		sf::Texture texture;
		sf::Vector2i position;
		std::shared_ptr<Floor> floor;
	private:

};