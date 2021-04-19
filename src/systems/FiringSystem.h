#pragma once

#include <protegon.h>

#include "components/Components.h"
#include "factories/Factories.h"

class FiringSystem : public ecs::System<AmmoComponent, Transform> {
public:
	void Update() override {
		for (auto [entity, ammo, transform] : entities) {
			if (engine::InputHandler::KeyPressed(Key::SPACE) &&
				ammo.bullets > 0 &&
				ammo.timer.ElapsedSeconds() > ammo.reload_delay) {

				--ammo.bullets;
				CreateBullet(entity.GetManager(), ammo.lifetime, transform);
				entity.GetManager().Refresh();
				// Testart reload timer.
				ammo.timer.Start();
			}
		}
	}
};
