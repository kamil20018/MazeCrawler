#include "StateManager.h"




StateManager::StateManager() : add(false), replace(false), remove(false) {

}

StateManager::~StateManager() {

}

void StateManager::AddState(std::shared_ptr<State> toAdd, bool replace) {
	this->add = true;
	this->newState = std::move(toAdd);
	this->replace = replace;
}

void StateManager::PopCurrent() {
	this->remove = true;
}

void StateManager::ProcessStateChange() {
	if (this->remove and not this->stateStack.empty()) {
		if (this->stateStack.top()->getState() == States::ITEM_CHOOSE) {
			std::shared_ptr<ItemChooseState> itemChooseState = dynamic_pointer_cast<ItemChooseState>(stateStack.top());
			std::vector<std::shared_ptr<Item>> items = itemChooseState->getTakenItems();
			for (auto item : items) {
				item->print();
			}
			itemChooseState->test();
		}
		this->stateStack.pop();
		if (!stateStack.empty()) {
			stateStack.top()->Start();
		}
		this->remove = false;
	}

	if (this->add) {
		if (this->replace and not stateStack.empty()) {
			this->stateStack.pop();
		}

		if (not this->stateStack.empty()) {
			this->stateStack.top()->Pause();
		}

		if (not this->stateStack.empty()) { // check if inventory
			std::cout << (int)this->stateStack.top()->getState() << std::endl;
		}

		this->stateStack.push(std::move(this->newState));

		this->stateStack.top()->Init();
		this->stateStack.top()->Start();
		this->add = false;

	}
}

std::shared_ptr<State>& StateManager::GetCurrent() {
	return stateStack.top();
}