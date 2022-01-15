#pragma once
#include <SFML/Graphics.hpp>
#include "Constants.h"
#include "Hero.h"
class HeroStatus : public sf::Drawable {
	public:
		HeroStatus(HeroData* data);
		~HeroStatus();
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	private:
		HeroData* data;
};