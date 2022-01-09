#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <string>
extern const std::vector<sf::Vector2i> dirs;
extern std::map <std::string, sf::Color> colors;
namespace utils {
	extern void printVector(sf::Vector2i vec);
	extern void printVector(std::string prefix, sf::Vector2i vec);
}

