#pragma once

#include <protegon.h>

#include "components/Components.h"
#include "core/Hell.h"

static ecs::Entity CreateBullet(ecs::Manager& manager, double lifetime, const Transform& transform) {
	auto bullet = manager.CreateEntity();
	auto radius = 3;
	V2_int sprite_size{ 16, 16 };
	bullet.AddComponent<BulletComponent>(20); // damage
	bullet.AddComponent<LifetimeComponent>(lifetime);
	bullet.AddComponent<HitboxComponent>();
	bullet.AddComponent<ShapeComponent>(Circle(radius));
	bullet.AddComponent<TagComponent>(Hasher::HashCString("bullet"));

	// Calculate offset necessary to center the bullet.

	V2_double offset_from_top_left{ 5, 7 };
	V2_double distance_to_center{ -offset_from_top_left };
	V2_double rotated_offset{
		distance_to_center.x * std::cos(transform.rotation) - distance_to_center.y * std::sin(transform.rotation),
		distance_to_center.x * std::sin(transform.rotation) + distance_to_center.y * std::cos(transform.rotation)
	};
	auto offset{ offset_from_top_left + distance_to_center - rotated_offset };
	auto& transform_component = bullet.AddComponent<Transform>(transform.position - offset * Hell::GetScale(), transform.rotation);

	bullet.AddComponent<Color>(colors::BLACK);
	auto& rigid_body = bullet.AddComponent<RigidBody>();
	double speed = 10;
	rigid_body.velocity = speed * V2_double{ std::sin(transform_component.rotation), -std::cos(transform_component.rotation) };
	return bullet;
}