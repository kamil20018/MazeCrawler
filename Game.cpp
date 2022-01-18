#include <SFML/Graphics/CircleShape.hpp>

#include "Game.h"
#include "MainMenu.h"

Game::Game() : context(std::make_shared<Context>())
{
    this->context->window->create(sf::VideoMode(800, 800), "Snake Game", sf::Style::Close);
    this->context->window->setFramerateLimit(30);
    this->context->states->AddState(std::make_unique<MainMenu>(this->context));
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