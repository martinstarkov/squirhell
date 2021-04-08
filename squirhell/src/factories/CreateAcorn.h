#pragma once

#include <protegon.h>

#include "components/TagComponents.h"
#include "components/SpriteKeyComponent.h"
#include "components/HealthComponent.h"
#include "components/HitboxComponent.h"

#include "core/Hell.h"

static ecs::Entity CreateAcorn(ecs::Manager& manager, const V2_double& position) {
	auto acorn = manager.CreateEntity();

	V2_int size{ 16, 16 };
	auto radius = size.x / 2 * Hell::GetScale().x;
	acorn.AddComponent<TransformComponent>(position);
	acorn.AddComponent<SizeComponent>(size);
	acorn.AddComponent<ShootableComponent>();
	acorn.AddComponent<HealthComponent>(100); // hit points
	acorn.AddComponent<SpriteKeyComponent>("acorn");
	acorn.AddComponent<HitboxComponent>(new CircleHitbox(radius), V2_int{ radius, radius });

	return acorn;
}