#include <SFML/Graphics/CircleShape.hpp>

#include "Game.h"
#include "MainMenu.h"
#include "InventoryState.h"

#include "UiTestState.h"

Game::Game() : context(std::make_shared<Context>()){
    this->context->window->create(sf::VideoMode(1200, 800), "Maze Crawler", sf::Style::Close);
    this->context->window->setFramerateLimit(60);
    
    this->context->states->AddState(std::make_shared<UiTestState>(this->context));

    //this->context->states->AddState(std::make_unique<MainMenu>(this->context));
    //this->context->states->InitInventory(this->context);
}

Game::~Game()
{
}

void Game::Run()
{

    sf::Clock clock;
    sf::Time timeSinceLastFrame = sf::Time::Zero;

    while (this->context->window->isOpen())
    {
        timeSinceLastFrame += clock.restart();

        while (timeSinceLastFrame > TIME_PER_FRAME)
        {
            timeSinceLastFrame -= TIME_PER_FRAME;

            this->context->states->ProcessStateChange();
            this->context->states->GetCurrent()->ProcessInput();
            this->context->states->GetCurrent()->Update();
            this->context->states->GetCurrent()->Draw();
        }
    }
}