#pragma once

#include <protegon.h>

#include "components/TagComponents.h"

#include "systems/MovementSystem.h"
#include "systems/RigidBodySystem.h"
#include "systems/BulletRenderSystem.h"
#include "systems/FiringSystem.h"

#include "factories/CreatePlayer.h"
#include "factories/CreateBullet.h"

class Hell : public engine::BaseWorld {
public:
	V2_int player_size{ 16, 16 };
	V2_double scale{ 4, 4 };
	engine::Timer timer;
	void Create() {
		player = CreatePlayer(manager, player_size, scale);
		manager.Refresh();
		timer.Start();
	}
	virtual void Update() {
		auto [tc, sc, rc, rbc] = player.GetComponents<TransformComponent, EntitySizeComponent, RenderComponent, RigidBodyComponent>();
		manager.UpdateSystem<FiringSystem>();
		manager.UpdateSystem<MovementSystem>();
		manager.UpdateSystem<RigidBodySystem>();
		manager.UpdateSystem<LifetimeSystem>();
	}
	virtual void Render() {

		manager.UpdateSystem<BulletRenderSystem>();
		auto [tc, sc, rc, rbc] = player.GetComponents<TransformComponent, EntitySizeComponent, RenderComponent, RigidBodyComponent>();
		engine::TextureManager::DrawRectangle("player", { 0,0 }, sc.size, tc.position, sc.size * sc.scale, Flip::NONE, nullptr, engine::math::RadiansToDegrees(tc.rotation));
	}
	virtual void Reset() {}
	virtual void Clear() {}
	virtual void SetPlayer(const ecs::Entity& new_player) {
		player = new_player;
	}
	virtual ecs::Entity& GetPlayer() {
		return player;
	}
	virtual ecs::Manager& GetManager() {
		return manager;
	}
private:
	ecs::Entity player;
	ecs::Manager manager;
	ecs::Entity bullet;
};