#pragma once

#include <protegon.h>

#include "components/Components.h"

#include "core/Hell.h"

static ecs::Entity CreateHealthPack(ecs::Manager& manager, const V2_double& position, const int health) {
	auto health_pack = manager.CreateEntity();

	V2_int sprite_size{ 8, 8 };
	auto radius = sprite_size.x / 2 * Hell::GetScale().x;
	health_pack.AddComponent<HealthPackComponent>(health);
	health_pack.AddComponent<ItemComponent>();
	health_pack.AddComponent<TransformComponent>(Transform{ position });
	health_pack.AddComponent<SpriteKeyComponent>("healthpack", sprite_size);
	health_pack.AddComponent<ShapeComponent>(Circle(radius));
	health_pack.AddComponent<HitboxComponent>();
	return health_pack;
}