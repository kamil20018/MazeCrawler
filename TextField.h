#pragma once

#include <SFML/Graphics.hpp>
#include "Constants.h"

enum class Alignment {
	MIDDLE_LEFT,
	MIDDLE_MIDDLE,
	MIDDLE_RIGHT,
};

class TextField : public sf::Drawable {

public:
	TextField();
	TextField(std::string text, sf::Vector2f position, const sf::Font& font, bool hardBounds);
	void setAlignment(Alignment alignment);
	void setBackgroundColor(sf::Color color);
	void setScalingBoundsSize(sf::Vector2f boundsSize);
	void setHardBoundsSize(sf::Vector2f boundsSize);
	void setFontSize(int size);
	void setFontColor(sf::Color color);
	void setSelected(bool selected);
	void setPadding(float padding);
	void setString(std::string str);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
	void update();
	sf::Vector2f position;
	sf::Vector2f hardBoundsSize;
	sf::Vector2f scalingBoundsSize;
	sf::Text text;
	sf::RectangleShape background;
	sf::Font font;
	Alignment alignment = Alignment::MIDDLE_MIDDLE;
	float padding = 0.0f;
	bool scalingBounds = false;
	bool hardBounds = true;
	bool wasSelected = false;
};