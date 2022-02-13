#pragma once

#include <memory>

#include <SFML/Graphics/Text.hpp>

#include "State.h"
#include "Game.h"
#include "GamePlay.h"
#include "Constants.h"
class MainMenu : public State
{
private:
    std::shared_ptr<Context> context;
    sf::Text gameTitle;
    sf::Text playButton;
    sf::Text exitButton;

    bool isPlayButtonSelected;
    bool isPlayButtonPressed;

    bool isExitButtonSelected;
    bool isExitButtonPressed;

public:
    MainMenu(std::shared_ptr<Context>& context);
    ~MainMenu();

    void Init() override;
    void ProcessInput() override;
    void Update() override;
    void Draw() override;
    States getState() override;
};