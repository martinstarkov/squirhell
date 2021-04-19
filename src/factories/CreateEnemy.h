#pragma once

#include <protegon.h>

#include "components/Components.h"
#include "core/Hell.h"

static ecs::Entity CreateEnemy(ecs::Manager& manager, const V2_double& position) {
	auto enemy = manager.CreateEntity();

	V2_int sprite_size{ 16, 16 };
	auto radius = 5 * Hell::GetScale().x;
	auto& pc = enemy.AddComponent<Transform>(position);
	enemy.AddComponent<ShootableComponent>();
	enemy.AddComponent<HealthComponent>(100); // hit points
	enemy.AddComponent<EnemyComponent>(20); // damage points
	enemy.AddComponent<AIMovementComponent>(1); // speed
	enemy.AddComponent<SpriteKeyComponent>("enemy", sprite_size);
	enemy.AddComponent<RigidBody>();
	enemy.AddComponent<HitboxComponent>(V2_int{ 0, 2 });
	enemy.AddComponent<ShapeComponent>(Circle(radius));

	return enemy;
}