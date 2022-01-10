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

enum States {
    HERO_TURN,
    ENEMY_TURN
};



int main()
{
    States state = HERO_TURN;

    std::shared_ptr<Hero> hero = std::make_shared<Hero>(sf::Vector2i(1, 1));
    std::shared_ptr<Floor> floor = std::make_shared<Floor>(10, 10, hero);
    Goblin goblin(sf::Vector2i(3, 3), floor);

    //window init
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Cellular Automata");
    window.setFramerateLimit(30);

    float middlePos = (float)(WINDOW_HEIGHT - 75) / 2;

    //app loop
    while (window.isOpen()) {
        sf::Event evnt;
        while (window.pollEvent(evnt)) {
            if (evnt.type == sf::Event::Closed) {
                window.close();
            }
        }
        sf::Vector2i heroPos = hero->getPosition();
        bool triedToMove = false;
        bool heroMoved = false;
        bool skippedTurn = false;
        switch (state) {

            case HERO_TURN:

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) and floor->canMoveTo(heroPos, up)) {
                    triedToMove = true;
                    heroMoved = hero->move(up);
                    //if (not hero->move(up) and not hero->canMove()) {
                    //    hero->turnPassed();
                    //    state = ENEMY_TURN;
                    //    std::cout << "hero turn passed" << std::endl;
                    //}
                    //goblin.canSeeHero();
                    
                }
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) and floor->canMoveTo(heroPos, down)) {
                    triedToMove = true;
                    heroMoved = hero->move(down);
                    //if (not hero->move(down) and not hero->canMove()) {
                    //    hero->turnPassed();
                    //    state = ENEMY_TURN;
                    //    std::cout << "hero turn passed" << std::endl;
                    //}
                    //goblin.canSeeHero();
                }
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) and floor->canMoveTo(heroPos, left)) {
                    triedToMove = true;
                    heroMoved = hero->move(left);
                    //if (not hero->move(left) and not hero->canMove()) {
                    //    hero->turnPassed();
                    //    state = ENEMY_TURN;
                    //    std::cout << "hero turn passed" << std::endl;
                    //}
                    //goblin.canSeeHero();
                }
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) and floor->canMoveTo(heroPos, right)) {
                    triedToMove = true;
                    heroMoved = hero->move(right);
                    //if (not hero->move(right) and not hero->canMove()) {
                    //    hero->turnPassed();
                    //    state = ENEMY_TURN;
                    //    std::cout << "hero turn passed" << std::endl;
                    //}
                    //goblin.canSeeHero();
                }
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
                    triedToMove = true;
                    skippedTurn = true;
                    //hero->turnPassed();
                    //state = ENEMY_TURN;
                    //std::cout << "hero turn passed" << std::endl;
                    //goblin.canSeeHero();
                }
                if (heroMoved) {
                    goblin.canSeeHero();
                }
                else if ((triedToMove and not hero->canMove()) or skippedTurn) {
                    hero->turnPassed();
                    state = ENEMY_TURN;
                    std::cout << "hero turn passed" << std::endl;
                }


                break;
            case ENEMY_TURN:
                goblin.takeTurn();
                state = HERO_TURN;

        }
        

        window.clear(colors["red"]);


        sf::Texture floorTexture = floor->getTexture();

        sf::Sprite mazeSprite;
        mazeSprite.setTexture(floorTexture);
        mazeSprite.setPosition(middlePos, middlePos);
        mazeSprite.move(-heroPos.x * 75, -heroPos.y * 75);

        sf::Sprite heroSprite;
        heroSprite.setTexture(hero->getTexture());
        heroSprite.setPosition(middlePos, middlePos);

        sf::Sprite goblinSprite;
        goblinSprite.setTexture(goblin.getTexture());
        sf::Vector2i toHero = hero->getPosition() - goblin.getPosition();
        goblinSprite.setPosition(middlePos - toHero.x * 75, middlePos - toHero.y * 75);
        

        

        window.draw(mazeSprite);
        window.draw(heroSprite);
        window.draw(goblinSprite);
        window.display();
    }
    
    return 0;
}

