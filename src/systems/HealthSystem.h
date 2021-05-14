#pragma once

#include <protegon.h>

#include "components/Components.h"
#include "factories/Factories.h"

class HealthSystem : public ecs::System<HealthComponent> {
public:
	void Update() override {
		engine::RNG<double> rng{ 0,1 };
		for (auto [entity, health] : entities) {
			if (health.health_points <= 0) {
				if (!entity.HasComponent<PlayerInputComponent>()) {
					if (entity.HasComponent<EnemyComponent>() && entity.HasComponent<TransformComponent>() && rng() < 0.333) {
						auto drop_position = entity.GetComponent<TransformComponent>().transform.position;
						auto [player, input, player_health] = GetManager().GetUniqueEntityAndComponents<PlayerInputComponent, HealthComponent>();
						if (player_health.health_points < player_health.max_health) {
							if (rng() < 0.5) {
								CreateAmmoPack(GetManager(), drop_position, 20);
							} else {
								CreateHealthPack(GetManager(), drop_position, 50);
							}
						} else {
							CreateAmmoPack(GetManager(), drop_position, 20);
						}
					}
					entity.Destroy();
				} else {
					PrintLine("Loading Death Screen");
					CreateDeathScreen(GetManager());
				}
			} else if (health.health_points > health.max_health) {
				health.health_points = health.max_health;
			}
		}
		GetManager().Refresh();
	}
};