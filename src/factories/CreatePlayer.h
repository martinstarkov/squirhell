#pragma once

#include <protegon.h>

#include "components/Components.h"

using namespace engine;

static ecs::Entity CreatePlayer(ecs::Manager& manager) {
	V2_int sprite_size{ 16, 16 };
	auto player = manager.CreateEntity();
	player.AddComponent<PlayerInputComponent>();
	player.AddComponent<InventoryComponent2>();
	auto& timer = player.AddComponent<WaveTimerComponent>();
	timer.next = 5;
	player.AddComponent<HealthComponent>(100);
	player.AddComponent<AmmoComponent>(100, 0.1, 1); // bullets, reload delay, lifetime
	auto& pc = player.AddComponent<TransformComponent>(Transform{ V2_int{ 400, 300 } });
	player.AddComponent<SpriteKeyComponent>("player", sprite_size);
	player.AddComponent<ColorComponent>(colors::BLUE);
	auto radius = 5 * Hell::GetScale().x;
	player.AddComponent<TagComponent>(Hasher::HashCString("player"));
	player.AddComponent<RigidBodyComponent>();
	player.AddComponent<ShapeComponent>(Circle(radius));
	player.AddComponent<RangeComponent>((5.0 + 16.0 + 16.0) * Hell::GetScale().x);
	auto& hitbox = player.AddComponent<HitboxComponent>(V2_int{ 0, 3 });
	hitbox.ignored_tags.emplace(Hasher::HashCString("bullet"));
	return player;
}