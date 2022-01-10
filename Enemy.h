#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Floor.h"

class Floor;

class Enemy {
	public:
		virtual void takeTurn() = 0;
		Enemy(sf::Vector2i position, std::shared_ptr<Floor> floor);
		sf::Texture& getTexture();
		sf::Vector2i getPosition();
		bool canSeeHero();
		bool canMove();
		bool isDead();
		
	protected:
		sf::Texture texture;
		sf::Vector2i position;
		std::shared_ptr<Floor> floor;
		std::vector<sf::Vector2i> pathToHero;
		int vision;
		void moveBy(sf::Vector2i moveBy);
		void moveTo(sf::Vector2i moveTo);

		float speed;
		float maxEnergy;
		float currEnergy;


		int currentHp;
		int maxHp;
		int meeleDmg;
	private:

};