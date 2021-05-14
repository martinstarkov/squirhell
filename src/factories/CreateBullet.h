#pragma once

#include <protegon.h>

#include "components/Components.h"
#include "core/Hell.h"

static ecs::Entity CreateBullet(ecs::Manager& manager, double lifetime, const Transform& transform, bool is_enemy_bullet) {
	auto bullet = manager.CreateEntity();
	auto radius = 3;
	V2_int sprite_size{ 16, 16 };
	if (is_enemy_bullet) {
		radius = 6;
		bullet.AddComponent<EnemyBulletComponent>(20); // damage
		bullet.AddComponent<ColorComponent>(colors::DARK_RED);
	} else {
		bullet.AddComponent<BulletComponent>(20); // damage
		bullet.AddComponent<TagComponent>(Hasher::HashCString("bullet"));
		bullet.AddComponent<ColorComponent>(colors::BLACK);
	}
	bullet.AddComponent<LifetimeComponent>(lifetime);
	auto& hitbox = bullet.AddComponent<HitboxComponent>();
	bullet.AddComponent<ShapeComponent>(Circle(radius));

	// Calculate offset necessary to center the bullet.
	//3 5
	V2_double offset_from_top_left{ 0, 5 };
	V2_double distance_to_center{ -offset_from_top_left };
	V2_double rotated_offset{
		distance_to_center.x * std::cos(transform.rotation) - distance_to_center.y * std::sin(transform.rotation),
		distance_to_center.x * std::sin(transform.rotation) + distance_to_center.y * std::cos(transform.rotation)
	};
	auto offset{ offset_from_top_left + distance_to_center - rotated_offset };
	auto& transform_component = bullet.AddComponent<TransformComponent>(Transform{ transform.position - offset * Hell::GetScale(), transform.rotation });

	auto& rigid_body = bullet.AddComponent<RigidBodyComponent>();
	double speed = 10;
	rigid_body.body.velocity = speed * V2_double{ std::sin(transform_component.transform.rotation), -std::cos(transform_component.transform.rotation) };
	return bullet;
}