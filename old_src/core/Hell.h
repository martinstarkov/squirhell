#pragma once

#include <protegon.h>

using namespace engine;

class Hell {
public:
	static void Generate(ecs::Manager& manager);
	static V2_double GetScale();
	void Create();
	void Update();
	void Render();
	ecs::Manager manager;
};