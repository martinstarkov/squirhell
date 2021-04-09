#pragma once

#include <protegon.h>

#include "components/TagComponents.h"
#include "components/HitboxComponent.h"

static ecs::Entity CreatePlayer(ecs::Manager& manager, const V2_int& sprite_size) {
	auto player = manager.CreateEntity();
	player.AddComponent<PlayerInputComponent>();
	player.AddComponent<HealthComponent>(100);
	player.AddComponent<AmmoComponent>(100, 0.1, 1); // bullets, reload delay, lifetime
	auto& pc = player.AddComponent<TransformComponent>(V2_int{ 400,300 });
	auto& sc = player.AddComponent<SizeComponent>(sprite_size);
	player.AddComponent<SpriteKeyComponent>("player");
	player.AddComponent<RenderComponent>(engine::BLUE);
	auto radius = sc.size.x / 2 * Hell::GetScale().x;
	auto circle = new Circle(sc.size.x / 2 * Hell::GetScale().x);
	auto body = new Body(std::move(circle), pc.position);
	player.AddComponent<RigidBodyComponent>(std::move(body));
	player.AddComponent<HitboxComponent>(new CircleHitbox(radius), V2_int{ radius, radius });
	return player;
}