#pragma once
#include "Constants.h"

const std::vector<sf::Vector2i> dirs{
    sf::Vector2i(1, 0),
    sf::Vector2i(0, 1),
    sf::Vector2i(-1, 0),
    sf::Vector2i(0, -1)
};

std::map <std::string, sf::Color> colors = {
    {"red", sf::Color::Red},
    {"green", sf::Color::Green},
    {"blue", sf::Color::Blue},
    {"white", sf::Color::White},
    {"black", sf::Color::Black},
    {"dark_grey", sf::Color(20, 20, 20)},
    {"medium_grey", sf::Color(30, 30, 30)}
};

namespace utils{
    void printVector(sf::Vector2i vec) {
        std::cout << "x: " << vec.x << " y: " << vec.y << std::endl;
    }

    void printVector(std::string prefix, sf::Vector2i vec) {
        std::cout << prefix << "x: " << vec.x << " y: " << vec.y << std::endl;
    }
}
