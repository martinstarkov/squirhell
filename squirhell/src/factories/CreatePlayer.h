#pragma once
#include <protegon.h>
#include "components/TagComponents.h"

ecs::Entity CreatePlayer(ecs::Manager& manager) {
	auto player = manager.CreateEntity();
	player.AddComponent<PlayerInputComponent>();
	auto& pc = player.AddComponent<TransformComponent>(V2_int{ 400,300 });
	auto& sc = player.AddComponent<SizeComponent>(V2_int{ 64,64 });
	player.AddComponent<RenderComponent>(engine::BLUE);
	engine::TextureManager::Load("player", "resources/player.png");
	auto circle = new Circle(sc.size.x / 2);
	auto body = new Body(std::move(circle), pc.position);
	player.AddComponent<RigidBodyComponent>(std::move(body));
	return player;
}