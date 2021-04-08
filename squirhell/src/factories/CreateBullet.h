#pragma once
#include <protegon.h>
#include "components/TagComponents.h"

ecs::Entity CreateBullet(ecs::Manager& manager, double lifetime, const TransformComponent& transform, const EntitySizeComponent& size_component) {
	auto bullet = manager.CreateEntity();
	bullet.AddComponent<BulletComponent>();
	bullet.AddComponent<LifetimeComponent>(lifetime);

	// Calculate offset necessary to center the bullet.

	V2_double offset_from_top_left{ 5, 7 };
	V2_double distance_to_center{ size_component.size / 2 - offset_from_top_left };
	V2_double rotated_offset{
		distance_to_center.x * std::cos(transform.rotation) - distance_to_center.y * std::sin(transform.rotation),
		distance_to_center.x * std::sin(transform.rotation) + distance_to_center.y * std::cos(transform.rotation)
	};
	auto offset{ offset_from_top_left + distance_to_center - rotated_offset };
	auto& bpc = bullet.AddComponent<TransformComponent>(transform.position + offset * size_component.scale);

	bullet.AddComponent<RenderComponent>(engine::BLACK);
	auto bullet_circle = new Circle(3);
	auto bullet_body = new Body(std::move(bullet_circle), bpc.position);
	auto& brbc = bullet.AddComponent<RigidBodyComponent>(std::move(bullet_body));
	double speed = 10;
	brbc.body->velocity = speed * V2_double{ std::sin(transform.rotation), -std::cos(transform.rotation) };
	return bullet;
}