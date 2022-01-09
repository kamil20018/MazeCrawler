#pragma once

#include <vector>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Hero.h"
#include "Constants.h"

class Floor {
	public:
		Floor(int width, int height, std::shared_ptr<Hero> hero);
		sf::Vector2i entrance;
		sf::Vector2i exit;
		const sf::Texture& getTexture();
		sf::RenderTexture renderTexture;
		bool canMoveTo(sf::Vector2i startPos, sf::Vector2i dir);

		

	private:
		std::vector<std::vector<bool>> horizontalWalls;
		std::vector<std::vector<bool>> verticalWalls;
		std::vector<std::vector<bool>> seenCells;
		void generateMaze(sf::Vector2i entrance);
		bool vectorInBounds(sf::Vector2i pos);
		int width;
		int height;
		int visibility;
		std::shared_ptr<Hero> hero;
		void getVisibleNeighbours(int depth, sf::Vector2i previousCell, sf::Vector2i currentCell, std::vector<sf::Vector2i>& visibleNeighbours);
};