#pragma once
#include <protegon.h>

class Hell : public engine::BaseWorld {
public:
	V2_double speed{ 5,5 };
	void Create() {
		player = manager.CreateEntity();
		manager.Refresh();
		auto& pc = player.AddComponent<TransformComponent>(V2_int{ 400,300 });
		auto& sc = player.AddComponent<SizeComponent>(V2_int{ 40,30 });
		player.AddComponent<RenderComponent>(engine::BLUE);
		engine::TextureManager::Load("player", "resources/player.png");
		auto circle = new Circle(sc.size.x / 2);
		auto body = new Body(circle, pc.position);
		player.AddComponent<RigidBodyComponent>(body);
	}
	virtual void Update() {
		auto [pc, sc, rc, rbc] = player.GetComponents<TransformComponent, SizeComponent, RenderComponent, RigidBodyComponent>();
		
		if (engine::InputHandler::KeyPressed(Key::W) && engine::InputHandler::KeyReleased(Key::S)) {
			rbc.body->velocity.y = -speed.y;
			pc.rotation = 0.0;
		} else if (engine::InputHandler::KeyPressed(Key::S) && engine::InputHandler::KeyReleased(Key::W)) {
			rbc.body->velocity.y = speed.y;
			pc.rotation = 180.0;
		} else {
			rbc.body->velocity.y = 0;
		}

		if (engine::InputHandler::KeyPressed(Key::A) && engine::InputHandler::KeyReleased(Key::D)) {
			rbc.body->velocity.x = -speed.x;
			pc.rotation = 270.0;
		} else if (engine::InputHandler::KeyPressed(Key::D) && engine::InputHandler::KeyReleased(Key::A)) {
			rbc.body->velocity.x = speed.x;
			pc.rotation = 90.0;
		} else {
			rbc.body->velocity.x = 0;
		}
		if ((engine::InputHandler::KeyPressed(Key::A) && engine::InputHandler::KeyPressed(Key::S)) || (engine::InputHandler::KeyPressed(Key::D) && engine::InputHandler::KeyPressed(Key::A))) {
		} else if (engine::InputHandler::KeyPressed(Key::W) && engine::InputHandler::KeyPressed(Key::D)) {
			pc.rotation = 0.0 + 45.0;
		} else if (engine::InputHandler::KeyPressed(Key::S) && engine::InputHandler::KeyPressed(Key::D)) {
			pc.rotation = 90 + 45.0;
		} else if (engine::InputHandler::KeyPressed(Key::S) && engine::InputHandler::KeyPressed(Key::A)) {
			pc.rotation = 180.0 + 45.0;
		} else if (engine::InputHandler::KeyPressed(Key::W) && engine::InputHandler::KeyPressed(Key::A)) {
			pc.rotation = 270.0 + 45.0;
		}
		pc.position += rbc.body->velocity;
	}
	virtual void Clear() {}
	virtual void Render() {
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
};