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
#include "EnemyManager.h"

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


    std::shared_ptr<EnemyManager> enemyManager = std::make_shared<EnemyManager>();
    std::shared_ptr<Hero> hero = std::make_shared<Hero>(sf::Vector2i(1, 1), enemyManager);
    std::shared_ptr<Floor> floor = std::make_shared<Floor>(15, 15, hero, enemyManager);

    std::shared_ptr<Goblin> goblin1 = std::make_shared<Goblin>(sf::Vector2i(3, 3), floor);
    std::shared_ptr<Goblin> goblin2 = std::make_shared<Goblin>(sf::Vector2i(3, 5), floor);
    std::shared_ptr<Goblin> goblin3 = std::make_shared<Goblin>(sf::Vector2i(3, 7), floor);



    //EnemyManager enemyManager;
    enemyManager->addEnemy(goblin1);
    enemyManager->addEnemy(goblin2);
    enemyManager->addEnemy(goblin3);

    //window init
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Cellular Automata");
    window.setFramerateLimit(15);

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
        sf::Vector2i newPos;
        sf::Vector2i movedBy(0, 0);

        bool endTurn = false;
        switch (state) {

            //case HERO_TURN:
            //    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) and floor->canMoveTo(heroPos, up)) {
            //        triedToMove = true;
            //        heroMoved = hero->move(up);
            //    }
            //    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) and floor->canMoveTo(heroPos, down)) {
            //        triedToMove = true;
            //        heroMoved = hero->move(down);
            //    }
            //    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) and floor->canMoveTo(heroPos, left)) {
            //        triedToMove = true;
            //        heroMoved = hero->move(left);
            //    }
            //    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) and floor->canMoveTo(heroPos, right)) {
            //        triedToMove = true;
            //        heroMoved = hero->move(right);
            //    }
            //    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
            //        skippedTurn = true;
            //    }
            //    if (heroMoved) {
            //        enemyManager->canSeeHero();
            //    }
            //    else if ((triedToMove and not hero->canMove()) or skippedTurn) {
            //        hero->turnPassed();
            //        state = ENEMY_TURN;
            //        std::cout << "hero turn passed" << std::endl;
            //    }
            //    break;
        case HERO_TURN:
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
                if (floor->canMoveTo(heroPos, up)) {
                    hero->move(up);
                }
                movedBy = up;
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
                if (floor->canMoveTo(heroPos, down)) {
                    hero->move(down);
                }
                movedBy = down;
                
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
                if (floor->canMoveTo(heroPos, left)) {
                    hero->move(left);
                }
                movedBy = left;
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
                if (floor->canMoveTo(heroPos, right)) {
                    hero->move(right);
                }
                movedBy = right;
                
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
                endTurn = true;
            }

            newPos = hero->getPosition();
            if (heroPos == newPos) {
                if (not hero->canMove()) { // if hero tried to move when he had no energy to move, we pass a turn
                    endTurn = true;
                }
                else if (enemyManager->isEnemyAt(heroPos + movedBy) and floor->isPathTo(heroPos, movedBy)) {
                    utils::printVector("attacked an enemy at: ", heroPos + movedBy);
                    hero->meeleAttack(heroPos + movedBy);
                }
            }
            else {
                enemyManager->canSeeHero();
            }

            if (endTurn) {
                hero->turnPassed();
                state = ENEMY_TURN;
                std::cout << "hero turn passed" << std::endl;
            }

            break;
        case ENEMY_TURN:
            enemyManager->takeTurn();
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
        

        

        window.draw(mazeSprite);
        window.draw(heroSprite);

        std::vector<std::pair<sf::Vector2i, sf::Texture&>> enemyTextures = enemyManager->getEnemyTextures();
        for (std::pair<sf::Vector2i, sf::Texture&> posAndTexture : enemyTextures) {
            sf::Sprite sprite;
            sprite.setTexture(posAndTexture.second);
            sf::Vector2i toHero = hero->getPosition() - posAndTexture.first;
            sprite.setPosition(middlePos - toHero.x * 75, middlePos - toHero.y * 75);
            window.draw(sprite);
        }

        
        window.display();
    }
    
    return 0;
}

