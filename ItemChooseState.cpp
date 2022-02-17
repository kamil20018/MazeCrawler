#include "ItemChooseState.h"

ItemChooseState::ItemChooseState(std::shared_ptr<Context>& context, std::vector<std::shared_ptr<Item>> items) {
	std::cout << "entered item choosing state" << std::endl;

	this->items = items;
	this->context = context;
	for (std::shared_ptr<Item> item : this->items) {
		item->print();
	}
	this->itemCount = (int)items.size();
	std::cout << items.size() << std::endl;
	this->finished = false;
	for (int i = 0; i < this->itemCount; i++) {
		this->removedItems.push_back(false);
		this->takenItems.push_back(false);
	}
	this->itemHeight = (float)SCREEN_HEIGHT / this->itemCount;
}

ItemChooseState::~ItemChooseState() {

}

void ItemChooseState::Init() {
	float totalHeight = this->textPadding;
	int index = 0;
	for (std::shared_ptr<Item> item : items) {
		TextField textField(item->getDescription(), sf::Vector2f(0.0f, this->itemHeight * index), this->context->assets->GetFont("pixel_font"), true);
		textField.setFontSize(25);
		textField.setHardBoundsSize(sf::Vector2f(this->itemListWidth, this->itemHeight));
		textField.setBackgroundColor(colors["black"]);
		textField.setFontColor(colors["white"]);
		textField.setBackgroundColor(colors["dark_grey"]);
		this->textFields.push_back(textField);
		index++;
	}
}

void ItemChooseState::ProcessInput() {
	sf::Event event;
	while (this->context->window->pollEvent(event)) {
		if (event.type == sf::Event::Closed) {
			this->context->window->close();
		}
		else if (event.type == sf::Event::KeyPressed) {
			switch (event.key.code) {
				case sf::Keyboard::Escape:
				case sf::Keyboard::Enter:
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

void ItemChooseState::Update() {
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

void ItemChooseState::Draw() {
	this->context->window->clear(colors["black"]);

	for (int i = 0; i < this->itemCount; i++) {
		if (i == this->currentField) {
			this->textFields[i].setSelected(true);
		}

		if (this->takenItems[i]) {
			this->textFields[i].setFontColor(colors["green"]);
		}
		else if (this->removedItems[i]) {
			this->textFields[i].setFontColor(colors["red"]);
		}
		else {
			this->textFields[i].setFontColor(colors["white"]);
		}

		this->context->window->draw(this->textFields[i]);
		this->textFields[i].setSelected(false);
	}

	this->context->window->display();
}

States ItemChooseState::getState() {
	return States::ITEM_CHOOSE;
}

std::vector<std::shared_ptr<Item>> ItemChooseState::getTakenItems() {
	std::vector<std::shared_ptr<Item>> returnItems;
	for (int i = 0; i < this->itemCount; i++) {
		if (this->takenItems[i]) {
			returnItems.push_back(this->items[i]);
		}
	}
	return returnItems;
}

void ItemChooseState::test() {
	std::cout << "method was called properly" << std::endl;
}
