#pragma once
#include <protegon.h>
#include "components/FlipComponent.h"

class Hell : public engine::BaseWorld {
public:
	V2_double speed{ 5,5 };
	void Create() {
		player = manager.CreateEntity();
		manager.Refresh();
		auto& pc = player.AddComponent<TransformComponent>(V2_int{ 400,300 });
		auto& sc = player.AddComponent<SizeComponent>(V2_int{ 40,30 });
		player.AddComponent<FlipComponent>();
		player.AddComponent<RenderComponent>(engine::BLUE);
		engine::TextureManager::Load("player", "resources/player.png");
		auto circle = new Circle(sc.size.x / 2);
		auto body = new Body(circle, pc.position);
		player.AddComponent<RigidBodyComponent>(body);
	}
	virtual void Update() {
		auto [pc, sc, rc, rbc, fc] = player.GetComponents<TransformComponent, SizeComponent, RenderComponent, RigidBodyComponent, FlipComponent>();
		if (engine::InputHandler::KeyPressed(Key::W) && !engine::InputHandler::KeyPressed(Key::S)) {
			rbc.body->velocity.y = -speed.y;
			fc.direction_y = Flip::NONE;
		} else if (engine::InputHandler::KeyPressed(Key::S) && !engine::InputHandler::KeyPressed(Key::W)) {
			rbc.body->velocity.y = speed.y;
			fc.direction_y = Flip::VERTICAL;
		} else {
			rbc.body->velocity.y = 0;
		}
		if (engine::InputHandler::KeyPressed(Key::A) && !engine::InputHandler::KeyPressed(Key::D)) {
			rbc.body->velocity.x = -speed.x;
			fc.direction_x = Flip::NONE;
		} else if (engine::InputHandler::KeyPressed(Key::D) && !engine::InputHandler::KeyPressed(Key::A)) {
			rbc.body->velocity.x = speed.x;
			fc.direction_x = Flip::HORIZONTAL;
		} else {
			rbc.body->velocity.x = 0;
		}
		pc.position += rbc.body->velocity;
	}
	virtual void Clear() {}
	virtual void Render() {
		auto [pc, sc, rc, rbc, fc] = player.GetComponents<TransformComponent, SizeComponent, RenderComponent, RigidBodyComponent, FlipComponent>();
		AABB player_rect{ pc.position, sc.size };
		engine::TextureManager::DrawRectangle("player", { 0,0 }, { 16, 16 }, pc.position, sc.size, static_cast<Flip>((int)fc.direction_x | (int)fc.direction_y));
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
};