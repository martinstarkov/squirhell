#pragma once

#include <protegon.h>

#include "systems/GameSystems.h"
#include "Hell.h"

// TODO: Add IsRunning boolean function to engine::Timer.

class Squirhell : public engine::Engine {
public:
	Hell hell;
	void Init() {
		engine::TextureManager::Load("player", "resources/player.png");
		engine::TextureManager::Load("acorn", "resources/acorn.png");
		engine::TextureManager::Load("ammopack", "resources/ammopack.png");
		hell.GetManager().AddSystem<FiringSystem>();
		hell.GetManager().AddSystem<MovementSystem>();
		hell.GetManager().AddSystem<SpriteRenderSystem>();
		hell.GetManager().AddSystem<HitboxCollisionSystem>();
		hell.GetManager().AddSystem<ShootableSystem>();
		hell.GetManager().AddSystem<PickUpSystem>();
		hell.GetManager().AddSystem<HealthSystem>();
		hell.GetManager().AddSystem<RigidBodySystem>();
		hell.GetManager().AddSystem<BulletRenderSystem>();
		hell.GetManager().AddSystem<LifetimeSystem>();
		hell.GetManager().AddSystem<StatDisplaySystem>();
		hell.Create();
	}
	void Update() {
		hell.Update();
	}
	void Render() {
		hell.Render();
	}
};