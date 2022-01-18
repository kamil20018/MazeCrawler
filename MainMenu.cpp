#include "MainMenu.h"

#include <SFML/Window/Event.hpp>

MainMenu::MainMenu(std::shared_ptr<Context>& context)
    : context(context), isPlayButtonSelected(true),
    isPlayButtonPressed(false), isExitButtonSelected(false),
    isExitButtonPressed(false)
{
}

MainMenu::~MainMenu()
{
}

void MainMenu::Init(){
    context->assets->AddFont("pixel_font", "Resources/Fonts/manaspc.ttf");

    // Title
    gameTitle.setFont(context->assets->GetFont("pixel_font"));
    gameTitle.setString("Maze Crawler");
    gameTitle.setOrigin(gameTitle.getLocalBounds().width / 2, gameTitle.getLocalBounds().height / 2);
    gameTitle.setPosition((float)context->window->getSize().x / 2,
        (float)context->window->getSize().y / 2 - 150.f);

    // Play Button
    playButton.setFont(context->assets->GetFont("pixel_font"));
    playButton.setString("Play");
    playButton.setOrigin(playButton.getLocalBounds().width / 2,
        playButton.getLocalBounds().height / 2);
    playButton.setPosition((float)context->window->getSize().x / 2,
        (float)context->window->getSize().y / 2 - 25.f);
    playButton.setCharacterSize(20);

    // Exit Button
    exitButton.setFont(context->assets->GetFont("pixel_font"));
    exitButton.setString("Exit");
    exitButton.setOrigin(exitButton.getLocalBounds().width / 2,
        exitButton.getLocalBounds().height / 2);
    exitButton.setPosition((float)context->window->getSize().x / 2,
        (float)context->window->getSize().y / 2 + 25.f);
    exitButton.setCharacterSize(20);
}

void MainMenu::ProcessInput(){
    sf::Event event;
    while (context->window->pollEvent(event)){
        if (event.type == sf::Event::Closed){
            context->window->close();
        }
        else if (event.type == sf::Event::KeyPressed){
            switch (event.key.code){
            case sf::Keyboard::Up:{
                if (!isPlayButtonSelected){
                    isPlayButtonSelected = true;
                    isExitButtonSelected = false;
                }
                break;
            }
            case sf::Keyboard::Down:{
                if (!isExitButtonSelected){
                    isPlayButtonSelected = false;
                    isExitButtonSelected = true;
                }
                break;
            }
            case sf::Keyboard::Return:{
                isPlayButtonPressed = false;
                isExitButtonPressed = false;

                if (isPlayButtonSelected){
                    isPlayButtonPressed = true;
                }
                else{
                    isExitButtonPressed = true;
                }

                break;
            }
            default:{
                break;
            }
            }
        }
    }
}

void MainMenu::Update(){
    if (isPlayButtonSelected){
        playButton.setFillColor(sf::Color::Black);
        exitButton.setFillColor(sf::Color::White);
    }
    else{
        exitButton.setFillColor(sf::Color::Black);
        playButton.setFillColor(sf::Color::White);
    }

    if (isPlayButtonPressed){
        context->states->AddState(std::make_unique<GamePlay>(context), true);
    }
    else if (isExitButtonPressed){
        context->window->close();
    }

}

void MainMenu::Draw(){
    context->window->clear(sf::Color::Blue);
    context->window->draw(gameTitle);
    context->window->draw(playButton);
    context->window->draw(exitButton);
    context->window->display();
}