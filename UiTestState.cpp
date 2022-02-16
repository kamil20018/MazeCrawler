#include "UiTestState.h"

UiTestState::UiTestState(std::shared_ptr<Context>& context) {
	this->context = context;
	context->assets->AddFont("pixel_font", "Resources/Fonts/manaspc.ttf");
	TextField temp(std::string("testfd\ngdgfdfgdfgdgf"), sf::Vector2f(20.0f, 20.0f), this->context->assets->GetFont("pixel_font"), true);
	this->field = temp;
	this->field.setHardBoundsSize(sf::Vector2f(500.0f, 500.0f));
	this->field.setSelected(true);
	this->field.setSelected(false);
	this->field.setAlignment(Alignment::MIDDLE_LEFT);
	this->field.setPadding(100.0f);
}

UiTestState::~UiTestState() {

}

void UiTestState::Init() {

}

void UiTestState::ProcessInput() {
	sf::Event event;
	while (this->context->window->pollEvent(event)) {
		if (event.type == sf::Event::Closed) {
			this->context->window->close();
		}
		else if (event.type == sf::Event::KeyPressed) {
			switch (event.key.code) {
				case sf::Keyboard::Escape:
					this->context->window->close();
					break;
			}
		}
	}
}


void UiTestState::Update() {

}

void UiTestState::Draw() {
	this->context->window->clear(colors["green"]);
	this->context->window->draw(field);
	this->context->window->display();
}

States UiTestState::getState() {
	return States();
}
