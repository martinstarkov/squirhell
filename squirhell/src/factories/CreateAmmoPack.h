#pragma once

#include <protegon.h>

#include "components/TagComponents.h"
#include "components/SpriteKeyComponent.h"
#include "components/HitboxComponent.h"
#include "components/AmmoPackComponent.h"

#include "core/Hell.h"

static ecs::Entity CreateAmmoPack(ecs::Manager& manager, const V2_double& position, const int ammo) {
	auto ammo_pack = manager.CreateEntity();

	V2_int size{ 8, 8 };
	auto radius = size.x / 2 * Hell::GetScale().x;
	ammo_pack.AddComponent<AmmoPackComponent>(ammo);
	ammo_pack.AddComponent<PickUpComponent>();
	ammo_pack.AddComponent<TransformComponent>(position);
	ammo_pack.AddComponent<SizeComponent>(size);
	ammo_pack.AddComponent<SpriteKeyComponent>("ammopack");
	ammo_pack.AddComponent<HitboxComponent>(new CircleHitbox(radius), V2_int{ radius, radius });

	return ammo_pack;
}