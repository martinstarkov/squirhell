#pragma once

#include "components/HitboxComponent.h"
#include "components/HealthComponent.h"
#include "components/AmmoPackComponent.h"
#include "components/AmmoComponent.h"

#include "core/Hell.h"

// TODO: Fix collision occuring earlier than expected on all sides (could have to do with velocity being added after, or something).

static bool CirclevsCircle(const V2_double& p1, const V2_double& p2, double r1, double r2) {
	// Calculate squared distance between centers
	auto d = p1 - p2;
	auto dist2 = d.DotProduct(d);
	// Spheres intersect if squared distance is less than squared sum of radii
	auto radiusSum = r1 + r2;
	return dist2 <= radiusSum * radiusSum;
}

static bool Contains(std::vector<ecs::Entity>& vector, const ecs::Entity& entity) {
	for (auto& e : vector) {
		if (e == entity) {
			return true;
		}
	}
	return false;
}

class HitboxCollisionSystem : public ecs::System<HitboxComponent, TransformComponent> {
public:
	void Update() {
		for (auto [entity, hc, tc] : entities) {
			auto type = hc.shape->GetType();
			for (auto [entity2, hc2, tc2] : entities) {
				if (entity != entity2) {
					auto type2 = hc2.shape->GetType();
					if (type == HitboxType::CIRCLE) {
						if (type2 == HitboxType::CIRCLE) {
							bool colliding = CirclevsCircle(tc.position + hc.offset, tc2.position + hc2.offset, hc.shape->GetRadius(), hc.shape->GetRadius());
							if (colliding && !Contains(hc.colliders, entity2)) {
								//LOG(tc.position << hc.offset << tc2.position << hc2.offset);
								hc.colliders.emplace_back(entity2);
							}
						} else if (type2 == HitboxType::RECTANGLE) {

						}
					} else if (type == HitboxType::RECTANGLE) {
						if (type2 == HitboxType::CIRCLE) {

						} else if (type2 == HitboxType::RECTANGLE) {

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
		for (auto [entity, sc, health, hc] : entities) {
			for (auto e : hc.colliders) {
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
		for (auto [entity, pic, ac, hc] : entities) {
			for (auto e : hc.colliders) {
				if (e.HasComponent<AmmoPackComponent>()) {
					ac.bullets += e.GetComponent<AmmoPackComponent>().ammo;
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
		for (auto [entity, pic, health, hc] : entities) {
			for (auto e : hc.colliders) {
				if (e.HasComponent<EnemyComponent>()) {
					health.health_points -= e.GetComponent<EnemyComponent>().damage;
					e.Destroy();
				}
			}
			hc.colliders.clear();
		}
		GetManager().Refresh();
	}
};