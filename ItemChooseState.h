#pragma once
#include "State.h"
#include "Game.h"
#include "Item.h"
#include "Constants.h"
#include "SFML/Graphics.hpp"
#include "TextField.h"

struct Context;
class ItemChooseState : public State {
public:
	ItemChooseState(std::shared_ptr<Context>& context, std::vector<std::shared_ptr<Item>> items);
	~ItemChooseState();
	void Init() override;
	void ProcessInput() override;
	void Update() override;
	void Draw() override;
	States getState() override;
	std::vector<std::shared_ptr<Item>> getTakenItems();
	void test();
private:
	std::vector<std::shared_ptr<Item>> items;
	std::shared_ptr<Context> context;
	bool finished;
	int itemCount;
	float itemFieldHeight;
	float textPadding = 10.0f;
	int currentField = 0;
	int changeFieldBy = 0;
	std::vector<TextField> textFields;
	std::vector<bool> takenItems;
	std::vector<bool> removedItems;
	bool taken;
	bool removed;
	float itemListWidth = (float)SCREEN_WIDTH / 3.0f;
	float itemHeight;
};

