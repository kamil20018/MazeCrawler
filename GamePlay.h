#pragma once

#include <memory>
#include <array>
#include <stdlib.h>
#include <time.h>
#include <SFML/Graphics.hpp>


#include "Floor.h"
#include "Hero.h"
#include "Constants.h"
#include "Enemy.h"
#include "Goblin.h"
#include "EnemyManager.h"
#include "HeroStatus.h"
#include "ItemChooseState.h"

#include "Game.h"
#include "State.h"



class GamePlay : public State {
public:
	GamePlay(std::shared_ptr<Context>& context);
	GamePlay(std::shared_ptr<Context>& context, std::shared_ptr<Hero> hero);
	~GamePlay();

	void Init() override;
	void firstInit(bool makeHero);
	void ProcessInput() override;
	void Update() override;
	void Draw() override;
	void Pause() override;
	void Start() override;
	States getState();
	static int level;

private:
	enum class Turn {
		HERO_TURN,
		ENEMY_TURN
	};

	std::shared_ptr<Context> context;
	bool isPaused = false;
	bool itemManagerOpen = false;
	const int WINDOW_WIDTH = 800;
	const int WINDOW_HEIGHT = 800;
	std::shared_ptr<EnemyManager> enemyManager;
	std::shared_ptr<Hero> hero;
	std::shared_ptr<Floor> floor;
	std::shared_ptr<HeroStatus> heroStatus;
	std::shared_ptr<AttackListener> attackListener;
	std::vector<std::shared_ptr<Item>> items;
	sf::Vector2i exit;
	float middlePos;
	Turn state;
	sf::Vector2i moveDir;

};