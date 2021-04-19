#pragma once

#include <protegon.h>

#include "components/Components.h"

using namespace engine;

static ecs::Entity CreatePlayer(ecs::Manager& manager) {
	V2_int sprite_size{ 16, 16 };
	auto player = manager.CreateEntity();
	player.AddComponent<PlayerInputComponent>();
	auto& timer = player.AddComponent<WaveTimerComponent>();
	timer.next = 5;
	player.AddComponent<HealthComponent>(100);
	player.AddComponent<AmmoComponent>(100, 0.1, 1); // bullets, reload delay, lifetime
	auto& pc = player.AddComponent<Transform>(V2_int{ 400, 300 });
	player.AddComponent<SpriteKeyComponent>("player");
	player.AddComponent<Color>(colors::BLUE);
	auto radius = sprite_size.x / 2 * Hell::GetScale().x;
	player.AddComponent<TagComponent>(Hasher::HashCString("player"));
	player.AddComponent<RigidBody>();
	player.AddComponent<ShapeComponent>(Circle(radius));
	auto& hitbox = player.AddComponent<HitboxComponent>();
	hitbox.ignored_tag_types.push_back(Hasher::HashCString("bullet"));
	return player;
}