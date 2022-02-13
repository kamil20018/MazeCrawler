#pragma once

#include <SFML/Graphics.hpp>
#include "Constants.h"
class State {
	public:
		State() {};
		virtual ~State() {};

		virtual void Init() = 0;
		virtual void ProcessInput() = 0;
		virtual void Update() = 0;
		virtual void Draw() = 0;
		virtual States getState() = 0;
		virtual void Pause() {};
		virtual void Start() {};
};