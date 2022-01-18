#pragma once
#include <SFML/Graphics.hpp>
#include "Constants.h"
#include "Hero.h"
#include <iostream>
#include <format>
class HeroStatus : public sf::Drawable {

	public:
		HeroStatus(HeroData *data, const sf::Font& font);
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	private:
		HeroData *data;
		sf::Font font;
};