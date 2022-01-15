#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <stdlib.h>

extern const std::vector<sf::Vector2i> dirs;
extern std::map <std::string, sf::Color> colors;

extern struct HeroData {
	const int& level;
	const float& currHp;
	const float& maxHp;
	const float& currXp;
	const float& xpToNextLevel;
	const float& currEnergy;
	const float& maxEnergy;
};

namespace utils {
	extern void printVector(sf::Vector2i vec);
	extern void printVector(std::string prefix, sf::Vector2i vec);
	extern int vectorDistance(sf::Vector2i vec1, sf::Vector2i vec2);

	template <typename T>
	bool isInVector(T item, std::vector<T> itemList)
	{
		for (T testItem : itemList) {
			if (item == testItem) {
				return true;
			}
		}
		return false;
	}
}

