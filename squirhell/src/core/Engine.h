#pragma once

#include <protegon.h>
#include "Hell.h"

class Squirhell : public engine::Engine {
public:
	Hell hell;
	void Init() {
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