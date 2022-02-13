#pragma once

#include <stack>
#include <memory>

#include <State.h>
#include "ItemChooseState.h"
#include "Item.h"
class StateManager {

	public:
		StateManager();
		~StateManager();

		void AddState(std::shared_ptr<State> toAdd, bool replace = false);
		void PopCurrent();
		void ProcessStateChange();
		std::shared_ptr<State>& GetCurrent();

	private:
		std::stack<std::shared_ptr<State>> stateStack;
		std::shared_ptr<State> newState;

		bool add;
		bool replace;
		bool remove;
};