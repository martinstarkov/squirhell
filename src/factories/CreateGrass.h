#pragma once

#include <protegon.h>

#include "components/Components.h"
#include "core/Hell.h"

inline void GrassCollision(ecs::Entity& target, const engine::Manifold& manifold) {
	if (target.HasComponent<TagComponent>()) {
		const auto& tag = target.GetComponent<TagComponent>();
		if (tag == "bullet" || target.HasComponent<BulletComponent>()) {
			target.Destroy();
		}
	}
}

static ecs::Entity CreateGrass(ecs::Manager& manager, const V2_double& position) {
	auto grass = manager.CreateEntity();

	V2_int sprite_size{ 16, 16 };
	auto scaled_size = sprite_size * Hell::GetScale();
	grass.AddComponent<TransformComponent>(Transform{ position });
	grass.AddComponent<SpriteKeyComponent>("grass", sprite_size);
	auto& hitbox = grass.AddComponent<HitboxComponent>();
	hitbox.function = &GrassCollision;
	grass.AddComponent<ShapeComponent>(AABB(scaled_size));
	grass.AddComponent<TagComponent>(Hasher::HashCString("grass"));
	hitbox.ignored_tag_types.push_back(Hasher::HashCString("player"));

	return grass;
}

static ecs::Entity CreateGrassItem(ecs::Manager& manager, const V2_double& position) {
	auto item = manager.CreateEntity();

	V2_int sprite_size{ 8, 8 };
	auto radius = sprite_size.x / 2 * Hell::GetScale().x;
	item.AddComponent<ItemComponent>();
	item.AddComponent<TagComponent>(Hasher::HashCString("grass"));
	item.AddComponent<PickUpComponent>();
	item.AddComponent<TransformComponent>(Transform{ position });
	item.AddComponent<SpriteKeyComponent>("grass", sprite_size);
	item.AddComponent<ShapeComponent>(Circle(radius));
	item.AddComponent<HitboxComponent>();
	return item;
}