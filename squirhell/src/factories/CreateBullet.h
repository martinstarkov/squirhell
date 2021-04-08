#pragma once
#include <protegon.h>
#include "components/TagComponents.h"

ecs::Entity CreateBullet(ecs::Manager& manager, const TransformComponent& transform) {
	V2_double scale{ 4, 4 };
	V2_double offset{ 5, 7 };
	V2_double center_offset{ 2, 0 };
	auto bullet = manager.CreateEntity();
	bullet.AddComponent<BulletComponent>();
	bullet.AddComponent<LifetimeComponent>(10);
	auto& bpc = bullet.AddComponent<TransformComponent>(transform.position);
	bullet.AddComponent<RenderComponent>(engine::BLACK);
	auto bullet_circle = new Circle(1);
	auto bullet_body = new Body(std::move(bullet_circle), bpc.position);
	auto& brbc = bullet.AddComponent<RigidBodyComponent>(std::move(bullet_body));
	double speed = 0;
	brbc.body->velocity = speed * V2_double{ std::sin(transform.rotation), -std::cos(transform.rotation) };
	return bullet;
}