#include "InventoryState.h"

InventoryState::InventoryState(std::shared_ptr<Context>& context){
    this->context = context;
    this->testCounter = 0;
}

InventoryState::~InventoryState() {

}

void InventoryState::Init() {

}

void InventoryState::ProcessInput() {
    sf::Event event;
    while (this->context->window->pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            this->context->window->close();
        }
        else if (event.type == sf::Event::KeyPressed) {
            switch (event.key.code) {
            case sf::Keyboard::Escape:
                this->context->states->PopCurrent();
                break;
            case sf::Keyboard::C:
                for (auto item : this->items) {
                    item->print();
                }
            }

        }
    }
}

void InventoryState::Update() {

}

void InventoryState::Draw() {
    this->context->window->clear(colors["green"]);
    this->context->window->display();
}

States InventoryState::getState() {
    return States::INVENTORY;
}

void InventoryState::AddItems(std::vector<std::shared_ptr<Item>> newItems){
    this->items.insert(this->items.end(), newItems.begin(), newItems.end());
}

