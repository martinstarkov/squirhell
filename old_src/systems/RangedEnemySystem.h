#pragma once

#include <protegon.h>

#include "components/Components.h"
#include "factories/Factories.h"

class RangedEnemySystem : public ecs::System<RangedEnemyComponent, AmmoComponent, TransformComponent> {
public:
	void Update() override {
		for (auto [entity, ranged, ammo, transform] : entities) {
			if (ammo.bullets > 0 &&
				ammo.timer.ElapsedSeconds() > ammo.reload_delay) {

				--ammo.bullets;
				CreateBullet(entity.GetManager(), ammo.lifetime, transform.transform, true);
				entity.GetManager().Refresh();
				// Testart reload timer.
				ammo.timer.Start();
			}
		}
	}
};