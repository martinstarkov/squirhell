#pragma once

#include <protegon.h>

#include "systems/GameSystems.h"
#include "Hell.h"

using namespace engine;

// TODO: Add IsRunning boolean function to engine::Timer.

class Squirhell : public Engine {
public:
	Hell hell;
	void Init() {
		hell.Create();
	}
	void Update() {
		hell.Update();
	}
	void Render() {
		hell.Render();
	}
};