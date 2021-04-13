#pragma once

#include <protegon.h>

#include "components/TagComponents.h"
#include "components/SpriteKeyComponent.h"
#include "components/HealthComponent.h"
#include "components/HitboxComponent.h"
#include "components/AIMovementComponent.h"

#include "core/Hell.h"

static ecs::Entity CreateEnemy(ecs::Manager& manager, const V2_double& position) {
	auto enemy = manager.CreateEntity();

	V2_int size{ 16, 16 };
	auto radius = size.x / 2 * Hell::GetScale().x;
	auto& pc = enemy.AddComponent<TransformComponent>(position);
	enemy.AddComponent<SizeComponent>(size);
	enemy.AddComponent<ShootableComponent>();
	enemy.AddComponent<HealthComponent>(100); // hit points
	enemy.AddComponent<EnemyComponent>(20); // damage points
	enemy.AddComponent<AIMovementComponent>(1); // speed
	enemy.AddComponent<SpriteKeyComponent>("enemy"); 
	auto circle = new Circle(radius);
	auto body = new Body(std::move(circle), pc.position);
	enemy.AddComponent<RigidBodyComponent>(std::move(body));
	enemy.AddComponent<HitboxComponent>(new CircleHitbox(radius), V2_int{ radius, radius });

	return enemy;
}