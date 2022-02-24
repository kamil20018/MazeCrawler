#include "SkillBox.h"

SkillBox::SkillBox() {

}

SkillBox::SkillBox(sf::Vector2f spriteSize, sf::Vector2f position) {
	this->spriteSize = spriteSize;
	this->position = position;
}

void SkillBox::setTexture(const sf::Texture& texture) {
	this->sprite = sf::Sprite(texture);
}

void SkillBox::setSpriteSize(sf::Vector2f size) {
	this->spriteSize = size;
	resizeSprite();
}

void SkillBox::setPosition(sf::Vector2f position) {
	this->position = position;
}

void SkillBox::setBgColor(sf::Color color) {
	this->bgColor = color;
}

void SkillBox::setBgPadding(float padding) {
	this->bgPadding = padding;
}

void SkillBox::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(this->sprite);
}

void SkillBox::resizeSprite() {
	this->sprite.setScale(sf::Vector2f(1.0f, 1.0f));

}
