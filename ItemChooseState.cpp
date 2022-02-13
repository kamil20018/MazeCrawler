#include "ItemChooseState.h"

ItemChooseState::ItemChooseState(std::shared_ptr<Context>& context, std::vector<std::shared_ptr<Item>> items){
    std::cout << "entered item choosing state" << std::endl;

	this->items = items;
	this->context = context;
	for (std::shared_ptr<Item> item : this->items) {
		item->print();
	}
    this->itemCount = items.size();
    std::cout << items.size() << std::endl;
    this->finished = false;
    for (int i = 0; i < this->itemCount; i++) {
        this->removedItems.push_back(false);
        this->takenItems.push_back(false);
    }
}

ItemChooseState::~ItemChooseState(){

}

void ItemChooseState::Init(){
    float totalHeight = this->textPadding;
    for (std::shared_ptr<Item> item: items) {
        sf::Text itemField;
        itemField.setString(item->getDescription());
        itemField.setFont(this->context->assets->GetFont("pixel_font"));
        itemField.setCharacterSize(23);
        itemField.setPosition(sf::Vector2f(this->textPadding, totalHeight));
        totalHeight += itemField.getGlobalBounds().height + this->textPadding;
        this->itemFields.push_back(itemField);
    }
    this->cursor.setString("> ");
    this->cursor.setFont(this->context->assets->GetFont("pixel_font"));
    this->cursor.setCharacterSize(23);
}

void ItemChooseState::ProcessInput(){
    sf::Event event;
    while (this->context->window->pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            this->context->window->close();
        }
        else if (event.type == sf::Event::KeyPressed){
            switch (event.key.code){
                case sf::Keyboard::Escape:
                    this->finished = true;
                    break;
                case sf::Keyboard::W:
                    this->changeFieldBy = -1;
                    break;
                case sf::Keyboard::S:
                    this->changeFieldBy = 1;
                    break;
                case sf::Keyboard::T:
                    this->taken = true;
                    break;
                case sf::Keyboard::R:
                    this->removed = true;
                    break;
            }
        }
    }
}

void ItemChooseState::Update(){
    if (this->finished) {
        std::cout << "exited item choosing state" << std::endl;
        this->context->states->PopCurrent();
    }
    if (this->changeFieldBy != 0) {
        this->currentField += this->changeFieldBy;
        if (this->currentField < 0) {
            this->currentField = this->itemCount - 1;
        }
        else if (this->currentField >= this->itemCount) {
            this->currentField = 0;
        }
        this->changeFieldBy = 0;
    }

    if (this->taken) {
        this->taken = false;
        this->takenItems[this->currentField] = true;
        this->removedItems[this->currentField] = false;
    }

    if (this->removed) {
        this->removed = false;
        this->removedItems[this->currentField] = true;
        this->takenItems[this->currentField] = false;
    }
}

void ItemChooseState::Draw(){
    this->context->window->clear(colors["black"]);
    bool drawCursor = false;
    for (int i = 0; i < this->itemCount; i++) {
        if (i == this->currentField) {
            drawCursor = true;
        }

        if (this->takenItems[i]) {
            this->itemFields[i].setFillColor(colors["green"]);
        }
        else if (this->removedItems[i]) {
            this->itemFields[i].setFillColor(colors["red"]);
        }
        else {
            this->itemFields[i].setFillColor(colors["white"]);
        }
        if (drawCursor) {
            this->cursor.setPosition(this->itemFields[i].getPosition());
            this->context->window->draw(this->cursor);
            this->itemFields[i].move(this->cursor.getGlobalBounds().width, 0);
            this->context->window->draw(this->itemFields[i]);
            this->itemFields[i].move(-this->cursor.getGlobalBounds().width, 0);
            drawCursor = false;
        }
        else {
            this->context->window->draw(this->itemFields[i]);
        }
        
    }

    this->context->window->display();
}

States ItemChooseState::getState(){
	return States::ITEM_CHOOSE;
}

std::vector<std::shared_ptr<Item>> ItemChooseState::getTakenItems()
{
    std::vector<std::shared_ptr<Item>> returnItems;
    for (int i = 0; i < this->itemCount; i++) {
        if (this->takenItems[i]) {
            returnItems.push_back(this->items[i]);
        }
    }
    return returnItems;
}

void ItemChooseState::test(){
    std::cout << "method was called properly" << std::endl;
}
