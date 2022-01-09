#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

#include "Enemy.h"


class Goblin : public Enemy {
	public:
		Goblin(sf::Vector2i initPos, std::shared_ptr<Floor> floor);
		void move(sf::Vector2i dir);
	private:
		void setTexture();
};