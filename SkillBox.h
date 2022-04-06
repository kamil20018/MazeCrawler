#pragma once

#include <SFML/Graphics.hpp>
#include "Constants.h"

class SkillBox : public sf::Drawable {
public:
	SkillBox();
	SkillBox(const sf::Texture& texture);
	SkillBox(const sf::Texture& texture, sf::Vector2f spriteSize, sf::Vector2f position);
	void setTexture(const sf::Texture& texture);
	void setSpriteSize(sf::Vector2f size);
	void setPosition(sf::Vector2f position);
	void setBgColor(sf::Color color);
	void setBgPadding(float padding);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
private:
	void updateBg();

	sf::Sprite sprite;
	sf::RectangleShape background;
	sf::Vector2f spriteSize;
	sf::Vector2f spritePos;
	sf::Color bgColor = colors["blue"];
	sf::Vector2f bgPadding;

};

