#include "StateManager.h"




StateManager::StateManager() : add(false), replace(false), remove(false), swap(false) {

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

	std::vector<std::shared_ptr<Item>> items;
	bool passItemsToInventory = false;

	if (this->remove and not this->stateStack.empty()) {

		if (this->stateStack.back()->getState() == States::ITEM_CHOOSE) {
			std::shared_ptr<ItemChooseState> itemChooseState = dynamic_pointer_cast<ItemChooseState>(stateStack.back());
			items = itemChooseState->getTakenItems();
			if (items.size() > 0) {
				passItemsToInventory = true;
			}
		}

		this->stateStack.pop_back();
		if (!stateStack.empty()) {
			stateStack.back()->Start();
		}
		this->remove = false;
	}

	if (this->add) {
		if (this->replace and not stateStack.empty()) {
			this->stateStack.pop_back();
		}

		if (not this->stateStack.empty()) {
			this->stateStack.back()->Pause();
		}

		if (not this->stateStack.empty()) { // check if inventory
			std::cout << (int)this->stateStack.back()->getState() << std::endl;
		}

		this->stateStack.push_back(std::move(this->newState));

		this->stateStack.back()->Init();
		this->stateStack.back()->Start();
		this->add = false;

	}

	if (this->swap and this->stateStack.size() >= 2) {
		this->swap = false;
		int swapIndex = this->stateStack.size() - 2;
		std::shared_ptr<State> temp = this->stateStack[swapIndex];
		this->stateStack.erase(this->stateStack.begin() + swapIndex);
		this->stateStack.push_back(temp);
	}

}

void StateManager::SwapPrevious(){
	this->swap = true;
}

std::shared_ptr<State>& StateManager::GetCurrent() {
	return stateStack.back();
}