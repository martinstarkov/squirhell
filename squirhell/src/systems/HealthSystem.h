#pragma once

#include <protegon.h>

#include "components/HealthComponent.h"

class HealthSystem : public ecs::System<HealthComponent> {
public:
	void Update() override {
		for (auto [entity, health] : entities) {
			if (health.health_points <= 0) {
				entity.Destroy();
			}
		}
		GetManager().Refresh();
	}
};