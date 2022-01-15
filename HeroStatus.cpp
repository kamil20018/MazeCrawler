#include "HeroStatus.h"



HeroStatus::HeroStatus(HeroData* data) {
	this->data = data;
}

HeroStatus::~HeroStatus() {
	//free(data);
}

void HeroStatus::draw(sf::RenderTarget& target, sf::RenderStates states) const
{

	const float maxWidth = 200.0f;
	const float barHeight = 25.0f;


	sf::Font font;
	if (!font.loadFromFile("Resources/Fonts/manaspc.ttf"))
	{
		std::cout << "you fucked up font" << std::endl;
	}

	int WINDOW_HEIGHT = 800;

	sf::RectangleShape barBg(sf::Vector2f(maxWidth, barHeight * 3));
	barBg.setFillColor(colors["white"]);

	sf::RectangleShape barOverlay(sf::Vector2f(maxWidth + 20, barHeight * 3 + 20));
	barOverlay.setFillColor(colors["black"]);

	float xpPercent = this->data->currXp / this->data->xpToNextLevel;
	sf::RectangleShape xpBar(sf::Vector2f(maxWidth * xpPercent, barHeight));
	xpBar.setFillColor(colors["blue"]);

	float hpPercent = this->data->currHp / this->data->maxHp;
	sf::RectangleShape hpBar(sf::Vector2f(maxWidth * hpPercent, barHeight));
	hpBar.setFillColor(colors["red"]);
	hpBar.setPosition(sf::Vector2f(0, barHeight));

	float staminaPercent = this->data->currEnergy / this->data->maxEnergy;
	sf::RectangleShape stBar(sf::Vector2f(maxWidth * staminaPercent, barHeight));
	stBar.setFillColor(colors["yellow"]);
	stBar.setPosition(sf::Vector2f(0, barHeight * 2));

	target.draw(barOverlay);
	target.draw(barBg);
	target.draw(xpBar);
	target.draw(hpBar);
	target.draw(stBar);
}
