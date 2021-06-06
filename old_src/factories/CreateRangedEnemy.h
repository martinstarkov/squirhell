#pragma once

#include <protegon.h>

#include "components/Components.h"
#include "core/Hell.h"

static ecs::Entity CreateRangedEnemy(ecs::Manager& manager, const V2_double& position) {
	auto ranged_enemy = manager.CreateEntity();

	V2_int sprite_size{ 16, 16 };
	auto radius = 5 * Hell::GetScale().x;
	auto& pc = ranged_enemy.AddComponent<TransformComponent>(Transform{ position });
	ranged_enemy.AddComponent<ShootableComponent>();
	ranged_enemy.AddComponent<HealthComponent>(100); // hit points
	ranged_enemy.AddComponent<EnemyComponent>(20); // damage points
	ranged_enemy.AddComponent<RangedEnemyComponent>(20); // damage points
	ranged_enemy.AddComponent<AmmoComponent>(100, 1); // damage points
	ranged_enemy.AddComponent<AIMovementComponent>(1); // speed
	ranged_enemy.AddComponent<SpriteKeyComponent>("ranged_enemy", sprite_size);
	ranged_enemy.AddComponent<RigidBodyComponent>();
	ranged_enemy.AddComponent<HitboxComponent>(V2_int{ 0, 2 });
	ranged_enemy.AddComponent<ShapeComponent>(Circle(radius));

	return ranged_enemy;
}