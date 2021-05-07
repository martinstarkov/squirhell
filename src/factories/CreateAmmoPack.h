#pragma once

#include <protegon.h>

#include "components/Components.h"

#include "core/Hell.h"

static ecs::Entity CreateAmmoPack(ecs::Manager& manager, const V2_double& position, const int ammo) {
	auto ammo_pack = manager.CreateEntity();

	V2_int sprite_size{ 8, 8 };
	auto radius = sprite_size.x / 2 * Hell::GetScale().x;
	ammo_pack.AddComponent<AmmoPackComponent>(ammo);
	ammo_pack.AddComponent<ItemComponent>();
	ammo_pack.AddComponent<TransformComponent>(Transform{ position });
	ammo_pack.AddComponent<SpriteKeyComponent>("ammopack", sprite_size);
	ammo_pack.AddComponent<ShapeComponent>(Circle(radius));
	ammo_pack.AddComponent<HitboxComponent>();
	return ammo_pack;
}