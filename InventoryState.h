#pragma once
#include "State.h"
#include "Game.h"
#include "SFML/Graphics.hpp"
#include "Constants.h"
#include <memory>

struct Context;

class InventoryState : public State{
    public: 
        InventoryState(std::shared_ptr<Context>& context);
        ~InventoryState();
        void Init() override;
        void ProcessInput() override;
        void Update() override;
        void Draw() override;
        States getState() override;
        void AddItems(std::vector<std::shared_ptr<Item>> newItems);
    private:
        std::shared_ptr<Context> context;
        std::vector<std::shared_ptr<Item>> items;
        int testCounter;
};

