#include "UiTestState.h"

UiTestState::UiTestState(std::shared_ptr<Context>& context){
	this->context = context;
}

UiTestState::~UiTestState(){

}

void UiTestState::Init(){
	context->assets->AddFont("pixel_font", "Resources/Fonts/manaspc.ttf");
}

void UiTestState::ProcessInput(){
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


void UiTestState::Update(){

}

void UiTestState::Draw(){
	this->context->window->clear(colors["green"]);
	this->context->window->display();
}

States UiTestState::getState(){
	return States();
}
