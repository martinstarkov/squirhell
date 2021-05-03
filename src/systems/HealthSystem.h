#pragma once

#include <protegon.h>

#include "components/Components.h"
#include "factories/Factories.h"

class HealthSystem : public ecs::System<HealthComponent> {
public:
	void Update() override {
		engine::RNG<int> rng{ 0,3 };
		for (auto [entity, health] : entities) {
			if (health.health_points <= 0) {
				if (!entity.HasComponent<PlayerInputComponent>()) {
					if (entity.HasComponent<EnemyComponent>() && entity.HasComponent<TransformComponent>() && rng() == 0) {
						CreateAmmoPack(GetManager(), entity.GetComponent<TransformComponent>().transform.position, 20);
					}
					entity.Destroy();
				} else {
					CreateDeathScreen(GetManager());
				}
			}
		}
		GetManager().Refresh();
	}
};