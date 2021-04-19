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
		TextureManager::Load("player", "resources/player.png");
		TextureManager::Load("acorn", "resources/acorn.png");
		TextureManager::Load("enemy", "resources/enemy.png");
		TextureManager::Load("ammopack", "resources/ammopack.png");
		FontManager::Load("retro_gaming_24", "resources/fonts/retro_gaming.ttf", 24);
		FontManager::Load("retro_gaming_16", "resources/fonts/retro_gaming.ttf", 16);
		hell.manager.AddSystem<FiringSystem>();
		hell.manager.AddSystem<MovementSystem>();
		hell.manager.AddSystem<AIMovementSystem>();
		hell.manager.AddSystem<SpriteRenderSystem>();
		hell.manager.AddSystem<HitboxCollisionSystem>();
		hell.manager.AddSystem<ShootableSystem>();
		hell.manager.AddSystem<DamageSystem>();
		hell.manager.AddSystem<PickUpSystem>();
		hell.manager.AddSystem<HealthSystem>();
		hell.manager.AddSystem<RigidBodySystem>();
		hell.manager.AddSystem<BulletRenderSystem>();
		hell.manager.AddSystem<LifetimeSystem>();
		hell.manager.AddSystem<StatDisplaySystem>();
		hell.manager.AddSystem<DeathScreenRenderSystem>();
		hell.Create();
	}
	void Update() {
		hell.Update();
	}
	void Render() {
		hell.Render();
	}
};