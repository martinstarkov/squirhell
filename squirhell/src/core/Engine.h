#pragma once

#include <protegon.h>
#include "Hell.h"

// TODO: Add IsRunning boolean function to engine::Timer.

class Squirhell : public engine::Engine {
public:
	Hell hell;
	void Init() {
		hell.GetManager().AddSystem<FiringSystem>();
		hell.GetManager().AddSystem<MovementSystem>();
		hell.GetManager().AddSystem<RigidBodySystem>();
		hell.GetManager().AddSystem<BulletRenderSystem>();
		hell.GetManager().AddSystem<LifetimeSystem>();
		hell.Create();
	}
	void Update() {
		hell.Update();
	}
	void Render() {
		hell.Render();
	}
};