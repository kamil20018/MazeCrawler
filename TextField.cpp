#include "TextField.h"

TextField::TextField() {
}

TextField::TextField(std::string text, sf::Vector2f position, const sf::Font& font, bool hardBounds = true) {

	if (hardBounds) {
		this->hardBounds = true;
		this->scalingBounds = false;
	}
	else {
		this->hardBounds = false;
		this->scalingBounds = true;
	}

	this->position = position;
	this->padding = 0.0f;
	this->wasSelected = false;
	sf::Text temp;
	temp.setFont(font);
	temp.setString(text);
	this->text = temp;

	this->scalingBoundsSize = sf::Vector2f(1.0f, 1.0f); // bacis behaviour - dynamic bounds
	this->hardBoundsSize = sf::Vector2f(this->text.getGlobalBounds().width, this->text.getGlobalBounds().height);
	this->alignment = Alignment::MIDDLE_MIDDLE; // basic behaviour - centered text
	this->background.setFillColor(colors["black"]);
	update();
}

void TextField::update() {


	sf::FloatRect textFieldBounds = this->text.getLocalBounds();

	float textWidth = textFieldBounds.width;
	float textHeight = textFieldBounds.height;
	sf::Vector2f textOffset = sf::Vector2f(-textFieldBounds.left, -textFieldBounds.top);

	float fieldWidth;
	float fieldHeight;

	if (hardBounds) {
		fieldWidth = this->hardBoundsSize.x;
		fieldHeight = this->hardBoundsSize.y;
	}
	else {
		fieldWidth = textWidth * (1.0f + (scalingBoundsSize.x / 100.0f));
		fieldHeight = textHeight * (1.0f + (scalingBoundsSize.y / 100.0f));
	}


	float horizCenter = (fieldWidth - textWidth) / 2.0f;
	float vertCenter = (fieldHeight - textHeight) / 2.0f;

	this->background.setSize(sf::Vector2f(fieldWidth, fieldHeight));
	this->background.setPosition(this->position);

	switch (this->alignment) {
		case Alignment::MIDDLE_LEFT:
			this->text.setPosition(this->position + sf::Vector2f(this->padding, vertCenter) + sf::Vector2f(-2.0f, -7.0f));
			break;
		case Alignment::MIDDLE_MIDDLE:
			this->text.setPosition(this->position + sf::Vector2f(horizCenter, vertCenter) + sf::Vector2f(-2.0f, -7.0f));
			break;
		case Alignment::MIDDLE_RIGHT:
			this->text.setPosition(this->position + sf::Vector2f(fieldWidth - textWidth - padding, vertCenter) + sf::Vector2f(-2.0f, -7.0f));
			break;
	}
	this->text.setFillColor(colors["black"]);

}


void TextField::setAlignment(Alignment alignment) {
	this->alignment = alignment;
	update();
}

void TextField::setBackgroundColor(sf::Color color) {
	this->background.setFillColor(color);
	update();
}

void TextField::setScalingBoundsSize(sf::Vector2f boundsSize) {
	if (boundsSize.x < 0.0f or boundsSize.y < 0.0f) throw std::invalid_argument("received negative value");
	this->scalingBoundsSize = boundsSize;
	update();
}

void TextField::setHardBoundsSize(sf::Vector2f boundsSize) {
	if (boundsSize.x < this->text.getGlobalBounds().width or boundsSize.y < this->text.getGlobalBounds().height) {
		throw std::invalid_argument("received negative value");
	}
	this->hardBoundsSize = boundsSize;
	update();
}

void TextField::setFontSize(int size) {
	this->text.setCharacterSize(size);
	update();
}

void TextField::setFontColor(sf::Color color) {
	this->text.setFillColor(color);
}

void TextField::setSelected(bool selected) {
	if (selected and not this->wasSelected) {
		this->text.setString((std::string)"> " + this->text.getString());
		this->wasSelected = true;
	}
	else if (this->wasSelected) {
		this->text.setString(this->text.getString().toAnsiString().substr(2));
		this->wasSelected = false;
	}

	update();
}

void TextField::setPadding(float padding) {
	this->padding = padding;
	update();
}

void TextField::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(this->background, states);
	target.draw(this->text, states);
}
