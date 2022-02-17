#pragma once
#include "State.h"
#include "Game.h"
#include "SFML/Graphics.hpp"
#include "Constants.h"
#include "Sword.h"
#include "TextField.h"
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
        std::vector<std::shared_ptr<Sword>> swords;
        std::vector<TextField> itemTypeSelectors;
        TextField itemNotImplemented;
        int columnCount = 2; //3rd column is visual only
        int currColumn;
        int colOneRow;
        int colTwoRow;

        int changeRowBy = 0;
        int changeColBy = 0;

        std::vector<ItemTypes> implementedItems;
};

