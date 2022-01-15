#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Floor.h"
#include "Constants.h"
class Floor;

class Enemy : public sf::Drawable {
	public:
		virtual void takeTurn() = 0;
		Enemy(sf::Vector2i position, std::shared_ptr<Floor> floor);
		sf::Vector2i getPosition();
		bool canSeeHero();
		bool canMove();
		bool isDead();
		void takeDamage(float damage);
		float getXpOnDeath();
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
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

		float xpOnDeath;

		float currentHp;
		float maxHp;
		float meeleDmg;


	private:

};