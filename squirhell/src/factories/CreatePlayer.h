#pragma once
#include <protegon.h>
#include "components/TagComponents.h"

ecs::Entity CreatePlayer(ecs::Manager& manager, const V2_int& size, const V2_double& scale) {
	auto player = manager.CreateEntity();
	player.AddComponent<PlayerInputComponent>();
	auto& pc = player.AddComponent<TransformComponent>(V2_int{ 400,300 });
	auto& sc = player.AddComponent<SizeComponent>(scale * size);
	player.AddComponent<RenderComponent>(engine::BLUE);
	engine::TextureManager::Load("player", "resources/player.png");
	auto circle = new Circle(sc.size.x / 2);
	auto body = new Body(std::move(circle), pc.position);
	player.AddComponent<RigidBodyComponent>(std::move(body));
	return player;
}