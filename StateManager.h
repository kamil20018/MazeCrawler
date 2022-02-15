#pragma once

#include <stack>
#include <memory>

#include <State.h>
#include "ItemChooseState.h"
#include "InventoryState.h"
#include "Item.h"

class InventoryState;
class StateManager {

	public:
		StateManager();
		~StateManager();

		void AddState(std::shared_ptr<State> toAdd, bool replace = false);
		void PopCurrent();
		void ProcessStateChange();
		void SwapPrevious();
		void ToInventoryState();
		void InitInventory(std::shared_ptr<Context>& context);
		std::shared_ptr<State>& GetCurrent();

	private:
		std::vector<std::shared_ptr<State>> stateStack;
		std::shared_ptr<State> newState;
		std::shared_ptr<InventoryState> inventoryState;

		bool add;
		bool replace;
		bool remove;
		bool swap;
};