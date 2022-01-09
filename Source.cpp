#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <conio.h>
#include <cstdlib> 
#include <ctime> 
#include <map>
#include <thread>
#include <memory>


#include "Floor.h"
#include "Hero.h"
#include "Constants.h"
#include "Enemy.h"
#include "Goblin.h"

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 800;

const sf::Vector2i up(0, -1);
const sf::Vector2i down(0, 1);
const sf::Vector2i left(-1, 0);
const sf::Vector2i right(1, 0);



int main()
{
    //Hero hero(sf::Vector2i(1, 1));
    std::shared_ptr<Hero> hero = std::make_shared<Hero>(sf::Vector2i(1, 1));
    std::shared_ptr<Floor> floor = std::make_shared<Floor>(10, 10, hero);
    //Floor floor(10, 10, hero);
    Goblin goblin(sf::Vector2i(1, 1), floor);
    //window init
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Cellular Automata");
    window.setFramerateLimit(30);

    //app loop
    while (window.isOpen()) {
        sf::Event evnt;
        while (window.pollEvent(evnt)) {
            if (evnt.type == sf::Event::Closed) {
                window.close();
            }
        }

        sf::Vector2i heroPos = hero->getPosition();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) and floor->canMoveTo(heroPos, up)){ 
            hero->move(up);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) and floor->canMoveTo(heroPos, down)) {
            hero->move(down);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) and floor->canMoveTo(heroPos, left)) {
            hero->move(left);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) and floor->canMoveTo(heroPos, right)) {
            hero->move(right);
        }

        window.clear(colors["red"]);


        sf::Texture floorTexture = floor->getTexture();

        sf::Sprite mazeSprite;
        mazeSprite.setTexture(floorTexture);
        mazeSprite.setPosition(362.5, 362.5);
        mazeSprite.move(-heroPos.x * 75, -heroPos.y * 75);

        sf::Sprite heroSprite;
        heroSprite.setTexture(hero->getTexture());
        heroSprite.setPosition(362.5, 362.5);

        window.draw(mazeSprite);
        window.draw(heroSprite);
        window.display();
    }
    
    return 0;
}

