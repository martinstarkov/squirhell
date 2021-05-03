#pragma once

#include <protegon.h>

#include "components/Components.h"
#include "core/Hell.h"

inline void WallCollision(ecs::Entity& target, const engine::Manifold& manifold) {
	if (target.HasComponent<TagComponent>()) {
		const auto& tag = target.GetComponent<TagComponent>();
		if (tag == "bullet" || target.HasComponent<BulletComponent>()) {
			target.Destroy();
		}
	}
}

static ecs::Entity CreateWall(ecs::Manager& manager, const V2_double& position) {
	auto wall = manager.CreateEntity();

	V2_int sprite_size{ 16, 16 };
	auto scaled_size = sprite_size * Hell::GetScale();
	wall.AddComponent<TransformComponent>(Transform{ position });
	wall.AddComponent<SpriteKeyComponent>("hell_wall", sprite_size);
	auto& hitbox = wall.AddComponent<HitboxComponent>();
	hitbox.function = &WallCollision;
	wall.AddComponent<ShapeComponent>(AABB(scaled_size));
	wall.AddComponent<TagComponent>(Hasher::HashCString("hellwall"));

	return wall;
}