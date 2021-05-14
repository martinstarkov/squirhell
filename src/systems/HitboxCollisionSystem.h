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
					offset_transform2.transform.position += hitbox2.offset;
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

class ItemSystem : public ecs::System<InventoryComponent2, HitboxComponent> {
public:
	void Update() {
		for (auto [entity, inventory, hitbox] : entities) {
			for (auto collider : hitbox.colliders) {
				if (collider.HasComponent<ItemComponent>()) {
					if (collider.HasComponent<PickUpComponent>()) {
						inventory.Add(collider);
						collider.RemoveComponent<PickUpComponent>();
						collider.RemoveComponent<ItemComponent>();
						collider.RemoveComponent<HitboxComponent>();
					} else {
						if (collider.HasComponent<HealthPackComponent>() && entity.HasComponent<HealthComponent>()) {
							entity.GetComponent<HealthComponent>().health_points += collider.GetComponent<HealthPackComponent>().health;
						} else if (collider.HasComponent<AmmoPackComponent>() && entity.HasComponent<AmmoComponent>()) {
							entity.GetComponent<AmmoComponent>().bullets += collider.GetComponent<AmmoPackComponent>().ammo;
						}
						collider.Destroy();
					}
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
			for (auto collider : hitbox.colliders) {
				if (collider.HasComponent<EnemyComponent>()) {
					health.health_points -= collider.GetComponent<EnemyComponent>().damage;
					collider.Destroy();
				}
				else if (collider.HasComponent<EnemyBulletComponent>()) {
					health.health_points -= collider.GetComponent<EnemyBulletComponent>().damage;
					collider.Destroy();
				}
			}
			hitbox.colliders.clear();
		}
		GetManager().Refresh();
	}
};