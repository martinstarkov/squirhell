#pragma once
#include <protegon.h>
#include "components/TagComponents.h"
#include "systems/MovementSystem.h"

class Hell : public engine::BaseWorld {
public:
	void Create() {
		player = manager.CreateEntity();
		manager.AddSystem<MovementSystem>();
		manager.Refresh();
		player.AddComponent<PlayerInputComponent>();
		auto& pc = player.AddComponent<TransformComponent>(V2_int{ 400,300 });
		auto& sc = player.AddComponent<SizeComponent>(V2_int{ 40,30 });
		player.AddComponent<RenderComponent>(engine::BLUE);
		engine::TextureManager::Load("player", "resources/player.png");
		auto circle = new Circle(sc.size.x / 2);
		auto body = new Body(std::move(circle), pc.position);
		player.AddComponent<RigidBodyComponent>(std::move(body));

		bullet = manager.CreateEntity();
		manager.Refresh();
		bullet.AddComponent<BulletComponent>();
		auto& bpc = bullet.AddComponent<TransformComponent>(V2_int{ 200,400 });
		bullet.AddComponent<RenderComponent>(engine::BLACK);
		auto bullet_circle = new Circle(10);
		auto bullet_body = new Body(std::move(bullet_circle), bpc.position);
		auto& brbc = bullet.AddComponent<RigidBodyComponent>(std::move(bullet_body));
		brbc.body->velocity = V2_double{ 3,0 };

	}
	virtual void Update() {
		manager.UpdateSystem<MovementSystem>();
		auto entities = manager.GetEntityComponents<TransformComponent, RigidBodyComponent>();
		for (auto [entity, tc, rbc] : entities) {
			tc.position += rbc.body->velocity;
		}
	}
	virtual void Clear() {}
	virtual void Render() {
		auto entities = manager.GetEntityComponents<BulletComponent, TransformComponent, RenderComponent, RigidBodyComponent>();
		for (auto [entity, bc, tc, rc, rbc] : entities) {
			engine::TextureManager::DrawSolidCircle(tc.position, rbc.body->shape->GetRadius(), rc.color);
		}

		auto [pc, sc, rc, rbc] = player.GetComponents<TransformComponent, SizeComponent, RenderComponent, RigidBodyComponent>();
		AABB player_rect{ pc.position, sc.size };
		engine::TextureManager::DrawRectangle("player", { 0,0 }, { 16, 16 }, pc.position, sc.size, Flip::NONE, nullptr, pc.rotation);
	}
	virtual void Reset() {}
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