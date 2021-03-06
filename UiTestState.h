#pragma once

#include "UiTestState.h"
#include "Game.h"
#include "State.h"
#include "Constants.h"
#include "SkillBox.h"
#include <memory>

#include "TextField.h"

struct Context;

class UiTestState : public State {
public:
	UiTestState(std::shared_ptr<Context>& context);
	~UiTestState();
	void Init() override;
	void ProcessInput() override;
	void Update() override;
	void Draw() override;
	States getState() override;
private:
	std::shared_ptr<Context> context;
	TextField field;
	SkillBox box;
};

