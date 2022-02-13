#pragma once

#include <memory>

#include <SFML/Graphics/RenderWindow.hpp>

#include "AssetManager.h"
#include "StateManager.h"

class StateManager;

struct Context
{
    std::unique_ptr<AssetManager> assets;
    std::unique_ptr<StateManager> states;
    std::unique_ptr<sf::RenderWindow> window;

    Context()
    {
        assets = std::make_unique<AssetManager>();
        states = std::make_unique<StateManager>();
        window = std::make_unique<sf::RenderWindow>();
    }
};

class Game
{
private:
    std::shared_ptr<Context> context;
    const sf::Time TIME_PER_FRAME = sf::seconds(1.f / 60.f);

public:
    Game();
    ~Game();

    void Run();
};