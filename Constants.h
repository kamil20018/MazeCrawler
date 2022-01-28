#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <stdlib.h>

extern const std::vector<sf::Vector2i> dirs;
extern std::map <std::string, sf::Color> colors;

namespace dir {
	inline const sf::Vector2i up(0, -1);
	inline const sf::Vector2i down(0, 1);
	inline const sf::Vector2i left(-1, 0);
	inline const sf::Vector2i right(1, 0);
}



struct HeroData {
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
	extern int randInt(int lowerBound, int upperBound); //INCLUSIVE
	extern float randFloat(float lowerBound, float upperBound);
	bool isNonZero(sf::Vector2i vector);
	template <typename T>
	bool isInVector(T item, std::vector<T> itemList){
		for (T testItem : itemList) {
			if (item == testItem) {
				return true;
			}
		}
		return false;
	}


}

