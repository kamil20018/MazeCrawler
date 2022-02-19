#pragma once

#include <vector>
#include <optional>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Hero.h"
#include "Constants.h"
#include "EnemyManager.h"

class EnemyManager;
class Hero;
class Floor {

	public:
		Floor(int width, int height, std::shared_ptr<Hero> hero, std::shared_ptr<EnemyManager> enemyManager);
		sf::Vector2i entrance;
		sf::Vector2i exit;
		const sf::Texture& getTexture();
		sf::RenderTexture renderTexture;
		bool canMoveTo(sf::Vector2i startPos, sf::Vector2i dir);
		sf::Vector2i getHeroPos();
		std::vector<sf::Vector2i> getPath(sf::Vector2i start, sf::Vector2i end);
		bool isPathTo(sf::Vector2i startPos, sf::Vector2i dir);
		
	private:
		std::vector<std::vector<bool>> horizontalWalls;
		std::vector<std::vector<bool>> verticalWalls;
		std::vector<std::vector<bool>> seenCells;
		void generateMazeDfs(sf::Vector2i entrance);
		void generateMazeAlt();
		void generateMazeWilson();
		bool allVisited(std::vector<std::vector<bool>> maze);
		bool vectorInBounds(sf::Vector2i pos);
		int width;
		int height;
		std::shared_ptr<Hero> hero;
		std::shared_ptr<EnemyManager> enemyManager;
		void getVisibleNeighbours(int depth, sf::Vector2i previousCell, sf::Vector2i currentCell, std::vector<sf::Vector2i>& visibleNeighbours);
};