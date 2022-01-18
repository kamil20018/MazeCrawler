#include "StateManager.h"




StateManager::StateManager() : add(false), replace(false), remove(false) {

}

StateManager::~StateManager() {

}

void StateManager::AddState(std::unique_ptr<State> toAdd, bool replace) {
	this->add = true;
	this->newState = std::move(toAdd);
	this->replace = replace;
}

void StateManager::PopCurrent() {
	this->remove = true;
}

void StateManager::ProcessStateChange() {
	if (this->remove and not this->stateStack.empty()) {
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
			stateStack.top()->Pause();
		}

		this->stateStack.push(std::move(this->newState));
		this->stateStack.top()->Init();
		this->stateStack.top()->Start();
		this->add = false;

	}
}

std::unique_ptr<State>& StateManager::GetCurrent() {
	return stateStack.top();
}