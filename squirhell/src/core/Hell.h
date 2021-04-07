#pragma once
#include <protegon.h>
#include "components/TagComponents.h"
#include "systems/MovementSystem.h"
#include "systems/RigidBodySystem.h"
#include "systems/BulletRenderSystem.h"
#include "factories/CreatePlayer.h"
#include "factories/CreateBullet.h"

class Hell : public engine::BaseWorld {
public:
	void Create() {
		player = CreatePlayer(manager);
		manager.Refresh();
	}
	virtual void Update() {
		auto [tc, sc, rc, rbc] = player.GetComponents<TransformComponent, SizeComponent, RenderComponent, RigidBodyComponent>();
		manager.UpdateSystem<MovementSystem>();
		manager.UpdateSystem<RigidBodySystem>();
		if (engine::InputHandler::KeyDown(Key::SPACE)) {
			bullet = CreateBullet(manager, tc);
			manager.Refresh();
		}
		manager.UpdateSystem<LifetimeSystem>();
	}
	virtual void Render() {
		manager.UpdateSystem<BulletRenderSystem>();

		auto [tc, sc, rc, rbc] = player.GetComponents<TransformComponent, SizeComponent, RenderComponent, RigidBodyComponent>();
		AABB player_rect{ tc.position, sc.size };
		engine::TextureManager::DrawRectangle("player", { 0,0 }, { 16, 16 }, tc.position, sc.size, Flip::NONE, nullptr, engine::math::RadiansToDegrees(tc.rotation));
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