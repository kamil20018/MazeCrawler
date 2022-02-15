#pragma once

#include "UiTestState.h"
#include "Game.h"
#include "State.h"
#include "Constants.h"
#include <memory>

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
};

