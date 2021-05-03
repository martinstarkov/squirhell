#pragma once

#include "components/Components.h"
#include "core/Hell.h"

class HitboxCollisionSystem : public ecs::System<HitboxComponent, TransformComponent, ShapeComponent> {
public:
	void Update() {
		for (auto [entity, hitbox, transform, shape] : entities) {
			for (auto [entity2, hitbox2, transform2, shape2] : entities) {
				if (entity != entity2 && !(HasExcludedTag(entity, hitbox2.ignored_tag_types) || HasExcludedTag(entity2, hitbox.ignored_tag_types))) {
					auto offset_transform{ transform };
					offset_transform.transform.position += hitbox.offset;
					auto offset_transform2{ transform2 };
					offset_transform2.transform.position += hitbox.offset;
					auto manifold{ StaticCollisionCheck(
						offset_transform.transform,
						offset_transform2.transform,
						shape.shape,
						shape2.shape
					)};
					if (!manifold.normal.IsZero()) {
						if (hitbox.function != nullptr) {
							hitbox.function(entity2, manifold);
						} else {
							transform.transform.position -= manifold.penetration;
							hitbox.colliders.emplace_back(entity2);
						}
					}
				}
			}
		}
	}
};

// TODO: Fix clearing of collisions, currently only clears collisions in damage system.

class ShootableSystem : public ecs::System<ShootableComponent, HealthComponent, HitboxComponent> {
public:
	void Update() {
		for (auto [entity, shootable, health, hitbox] : entities) {
			for (auto e : hitbox.colliders) {
				if (e.HasComponent<BulletComponent>()) {
					health.health_points -= e.GetComponent<BulletComponent>().damage;
					e.Destroy(); // destroy bullet upon hit.
				}
			}
		}
		GetManager().Refresh();
	}
};

class PickUpSystem : public ecs::System<PlayerInputComponent, AmmoComponent, HitboxComponent> {
public:
	void Update() {
		for (auto [entity, player, ammo, hitbox] : entities) {
			for (auto e : hitbox.colliders) {
				if (e.HasComponent<AmmoPackComponent>()) {
					ammo.bullets += e.GetComponent<AmmoPackComponent>().ammo;
					e.Destroy(); // destroy ammopack upon hit.
				}
			}
		}
		GetManager().Refresh();
	}
};

class DamageSystem : public ecs::System<PlayerInputComponent, HealthComponent, HitboxComponent> {
public:
	void Update() {
		for (auto [entity, player, health, hitbox] : entities) {
			for (auto e : hitbox.colliders) {
				if (e.HasComponent<EnemyComponent>()) {
					health.health_points -= e.GetComponent<EnemyComponent>().damage;
					e.Destroy();
				}
			}
			hitbox.colliders.clear();
		}
		GetManager().Refresh();
	}
};