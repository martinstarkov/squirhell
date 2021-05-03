#pragma once

#include <protegon.h>

#include "components/Components.h"
#include "factories/Factories.h"

class FiringSystem : public ecs::System<AmmoComponent, TransformComponent> {
public:
	void Update() override {
		for (auto [entity, ammo, transform] : entities) {
			if (engine::InputHandler::MousePressed(MouseButton::LEFT) &&
				ammo.bullets > 0 &&
				ammo.timer.ElapsedSeconds() > ammo.reload_delay) {

				--ammo.bullets;
				CreateBullet(entity.GetManager(), ammo.lifetime, transform.transform);
				entity.GetManager().Refresh();
				// Testart reload timer.
				ammo.timer.Start();
			}
		}
	}
};
