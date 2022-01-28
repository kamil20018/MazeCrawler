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
    {"yellow", sf::Color::Yellow},
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

    int vectorDistance(sf::Vector2i vec1, sf::Vector2i vec2) {
        return std::abs(vec1.x - vec2.x) + std::abs(vec2.y - vec2.y);
    }

    /// <summary>
    /// Warning: both lower and upper bounds are inclusive
    /// </summary>
    /// <param name="lowerBound"></param>
    /// <param name="upperBound"></param>
    /// <returns></returns>
    int randInt(int lowerBound, int upperBound){
        return rand() % (upperBound - lowerBound + 1) + lowerBound;
    }

    float randFloat(float lowerBound, float upperBound){
        return lowerBound + (rand() / (RAND_MAX / (upperBound - lowerBound)));
    }

    bool isNonZero(sf::Vector2i vector) {
        return vector != sf::Vector2i(0, 0);
    }
}
