#include "UiTestState.h"

UiTestState::UiTestState(std::shared_ptr<Context>& context) {
	this->context = context;
	this->context->assets->AddTexture("skill_1", "Resources/Textures/skill_1.png");
	SkillBox box(this->context->assets->GetTexture("skill_1"), sf::Vector2f(100.0f, 100.0f), sf::Vector2f(200.0f, 100.0f));
	box.setBgColor(colors["blue"]);
	this->box = box;
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
	this->context->window->draw(this->box);
	this->context->window->display();
}

States UiTestState::getState() {
	return States();
}
