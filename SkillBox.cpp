#include "SkillBox.h"

SkillBox::SkillBox() {

}

SkillBox::SkillBox(const sf::Texture& texture) {
	this->bgPadding = sf::Vector2f(10.0f, 10.0f);
	this->sprite = sf::Sprite(texture);
}

SkillBox::SkillBox(const sf::Texture& texture, sf::Vector2f spriteSize, sf::Vector2f position) {
	this->bgPadding = sf::Vector2f(10.0f, 10.0f);
	this->sprite = sf::Sprite(texture);
	setSpriteSize(spriteSize);
	this->sprite.setPosition(position);
	this->spritePos = position;
	updateBg();
}

void SkillBox::updateBg() {
	this->background.setPosition(this->spritePos - this->bgPadding / 2.0f);
	this->background.setSize(this->spriteSize + this->bgPadding);
}


void SkillBox::setTexture(const sf::Texture& texture) {
	this->sprite = sf::Sprite(texture);
}

sf::Vector2f operator/(const sf::Vector2f& v1, const sf::Vector2f v2) {
	float x = v1.x / v2.x;
	float y = v1.y / v2.y;
	return sf::Vector2f(x, y);
}

sf::Vector2f operator/(const sf::Vector2f& v1, float by) {
	float x = v1.x / by;
	float y = v1.y / by;
	return sf::Vector2f(x, y);
}

void SkillBox::setSpriteSize(sf::Vector2f size) {
	float width = this->sprite.getLocalBounds().width;
	float height = this->sprite.getLocalBounds().height;
	sf::Vector2f currSize(width, height);
	this->sprite.setScale(size / currSize);
	this->spriteSize = size;
	updateBg();
}

void SkillBox::setPosition(sf::Vector2f position) {
	this->spritePos = position;
	this->sprite.setPosition(position);
	updateBg();
}

void SkillBox::setBgColor(sf::Color color) {
	this->bgColor = color;
	this->background.setFillColor(color);
}

void SkillBox::setBgPadding(float padding) {
	this->bgPadding = sf::Vector2f(padding, padding);
}

void SkillBox::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(this->background, states);
	target.draw(this->sprite, states);
}



