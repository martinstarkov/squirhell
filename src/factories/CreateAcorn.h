#pragma once

#include <protegon.h>

#include "components/Components.h"
#include "core/Hell.h"

static ecs::Entity CreateAcorn(ecs::Manager& manager, const V2_double& position) {
	auto acorn = manager.CreateEntity();

	V2_int sprite_size{ 16, 16 };
	auto radius = sprite_size.x / 2 * Hell::GetScale().x;
	acorn.AddComponent<Transform>(position);
	acorn.AddComponent<ShootableComponent>();
	acorn.AddComponent<HealthComponent>(100); // hit points
	acorn.AddComponent<EnemyComponent>(60); // damage points
	acorn.AddComponent<SpriteKeyComponent>("acorn");
	acorn.AddComponent<HitboxComponent>();
	acorn.AddComponent<ShapeComponent>(Circle(radius));

	return acorn;
}