#include "HeroStatus.h"



HeroStatus::HeroStatus(HeroData* data, const sf::Font& font) {
	this->data = data;
	this->font = font;
	std::cout << this->data->xpToNextLevel << std::endl;
}


void HeroStatus::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	const float maxWidth = 200.0f;
	const float barHeight = 25.0f;

	int WINDOW_HEIGHT = 800;

	sf::RectangleShape barBg(sf::Vector2f(maxWidth, barHeight * 3));
	barBg.setFillColor(colors["white"]);

	sf::RectangleShape barOverlay(sf::Vector2f(maxWidth + 20, barHeight * 3 + 20));
	barOverlay.setFillColor(colors["black"]);


	//xp
	sf::Text xpText;
	xpText.setFont(this->font);
	xpText.setCharacterSize(20);
	xpText.setFillColor(colors["black"]);
	std::string xpTextFill = std::format("xp: {}/{}", this->data->currXp, this->data->xpToNextLevel);
	xpText.setString(xpTextFill);

	float xpPercent = this->data->currXp / this->data->xpToNextLevel;
	sf::RectangleShape xpBar(sf::Vector2f(maxWidth * xpPercent, barHeight));
	xpBar.setFillColor(colors["blue"]);

	//hp
	sf::Text hpText;
	hpText.setFont(this->font);
	hpText.setCharacterSize(20);
	hpText.setFillColor(colors["black"]);
	std::string hpTextFill = std::format("hp: {}/{}", this->data->currHp, this->data->maxHp);
	hpText.setString(hpTextFill);
	hpText.setPosition(sf::Vector2f(0, barHeight));

	float hpPercent = this->data->currHp / this->data->maxHp;
	sf::RectangleShape hpBar(sf::Vector2f(maxWidth * hpPercent, barHeight));
	hpBar.setFillColor(colors["red"]);
	hpBar.setPosition(sf::Vector2f(0, barHeight));

	//stamina

	sf::Text spText;
	spText.setFont(this->font);
	spText.setCharacterSize(20);
	spText.setFillColor(colors["black"]);
	std::string spTextFill = std::format("energy: {}/{}", (int)this->data->currStamina, (int)this->data->maxStamina);
	spText.setString(spTextFill);
	spText.setPosition(sf::Vector2f(0, 2 * barHeight));



	float staminaPercent = this->data->currEnergy / this->data->maxEnergy;
	sf::RectangleShape stBar(sf::Vector2f(maxWidth * staminaPercent, barHeight));
	stBar.setFillColor(colors["yellow"]);
	stBar.setPosition(sf::Vector2f(0, barHeight * 2));

	target.draw(barOverlay);
	target.draw(barBg);
	target.draw(xpBar);
	target.draw(hpBar);
	target.draw(stBar);

	target.draw(xpText);
	target.draw(hpText);
	target.draw(spText);
}
