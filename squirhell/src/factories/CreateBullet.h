#pragma once
#include <protegon.h>
#include "components/TagComponents.h"

ecs::Entity CreateBullet(ecs::Manager& manager, const TransformComponent& transform) {
	auto bullet = manager.CreateEntity();
	bullet.AddComponent<BulletComponent>();
	bullet.AddComponent<LifetimeComponent>(1);
	auto& bpc = bullet.AddComponent<TransformComponent>(transform.position);
	bullet.AddComponent<RenderComponent>(engine::BLACK);
	auto bullet_circle = new Circle(5);
	auto bullet_body = new Body(std::move(bullet_circle), bpc.position);
	auto& brbc = bullet.AddComponent<RigidBodyComponent>(std::move(bullet_body));
	double speed = 7;
	brbc.body->velocity = speed * V2_double{ std::sin(transform.rotation), -std::cos(transform.rotation) };
	return bullet;
}