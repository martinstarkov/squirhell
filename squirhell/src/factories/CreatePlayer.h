#pragma once
#include <protegon.h>
#include "components/TagComponents.h"
#include "components/EntitySizeComponent.h"

ecs::Entity CreatePlayer(ecs::Manager& manager, const V2_int& size, const V2_double& scale) {
	auto player = manager.CreateEntity();
	player.AddComponent<PlayerInputComponent>();
	player.AddComponent<AmmoComponent>(100, 0.1, 1); // bullets, reload delay, lifetime
	auto& pc = player.AddComponent<TransformComponent>(V2_int{ 400,300 });
	auto& sc = player.AddComponent<EntitySizeComponent>(size, scale);
	player.AddComponent<RenderComponent>(engine::BLUE);
	engine::TextureManager::Load("player", "resources/player.png");
	auto circle = new Circle(sc.size.x / 2);
	auto body = new Body(std::move(circle), pc.position);
	player.AddComponent<RigidBodyComponent>(std::move(body));
	return player;
}