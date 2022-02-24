#pragma once

#include <SFML/Graphics.hpp>
#include "Constants.h"

class SkillBox : public sf::Drawable {
	public: 
		SkillBox();
		SkillBox(sf::Vector2f spriteSize, sf::Vector2f position);
		void setTexture(const sf::Texture& texture);
		void setSpriteSize(sf::Vector2f size);
		void setPosition(sf::Vector2f position);
		void setBgColor(sf::Color color);
		void setBgPadding(float padding);
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	private:
		void resizeSprite();
		sf::Vector2f spriteSize;
		sf::Vector2f position;
		sf::Sprite sprite;
		sf::Color bgColor = colors["black"];
		float bgPadding = 1.0f;

};

