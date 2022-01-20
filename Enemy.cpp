#include "Enemy.h"

Enemy::Enemy(sf::Vector2i position, std::shared_ptr<Floor> floor) {
	this->position = position;
	this->floor = floor;
	this->vision = 3;
	this->speed = 2.3f;
}

sf::Vector2i Enemy::getPosition() {
	return this->position;
}

float Enemy::getXpOnDeath() {
	return this->xpOnDeath;
}

void Enemy::updatePathToHero() {
	std::vector<sf::Vector2i> path = floor->getPath(this->position, floor->getHeroPos());
	if (path.size() - 1 <= this->vision) {
		path.erase(path.begin());
		this->pathToHero = path;
	}
}

void Enemy::addAttackListener(std::shared_ptr<AttackListener> listener) {
	this->attackListener = listener;
}

void Enemy::moveBy(sf::Vector2i moveBy) {
	float moveEnergy = 100.0f / this->speed;
	this->currEnergy -= moveEnergy;
	this->position += moveBy;
}

void Enemy::moveTo(sf::Vector2i moveTo) {
	float moveEnergy = 100.0f / this->speed;
	this->currEnergy -= moveEnergy;
	this->position = moveTo;
}

bool Enemy::canMove() {
	return this->currEnergy > 100.0 / this->speed;
}

bool Enemy::isDead() {
	return this->currentHp < 0.1;
}

void Enemy::takeDamage(float damage) {
	this->currentHp -= damage;
	std::cout << "took damage, current hp: " << this->currentHp << std::endl;
}

void Enemy::addTexture(const sf::Texture& texture) {
	this->texture = texture;
}

void Enemy::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	int WINDOW_HEIGHT = 800;
	float middlePos = (float)(WINDOW_HEIGHT - 75) / 2;
	sf::Sprite enemySprite;
	enemySprite.setTexture(this->texture);

	sf::Vector2i toHero = this->floor->getHeroPos() - this->position;
	enemySprite.setPosition(middlePos - toHero.x * 75, middlePos - toHero.y * 75);
	target.draw(enemySprite, states);

	float filled = this->currentHp / this->maxHp;
	sf::RectangleShape healthBar(sf::Vector2f(75.0f * filled, 15.0f));
	healthBar.setFillColor(colors["red"]);
	healthBar.setPosition(middlePos - toHero.x * 75, middlePos - toHero.y * 75 - 15);
	target.draw(healthBar, states);
}